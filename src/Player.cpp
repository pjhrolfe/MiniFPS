#include "Player.h"
#include "Utilities.h"

namespace MiniFPS {
    Player::Player(Level* level, const Settings& settings) : level(level) {
        inputState = InputState();
        camera = Camera(settings.playerStartX, settings.playerStartY, settings.playerStartAngle,
                        settings.fieldOfView * PI_180, settings.screenWidth,
                        settings.screenHeight,
                        settings.renderDistance);
    }

    Player::Player() : level(nullptr) {}

    void Player::UpdateInputState() {
        inputState.mouseMotionX = 0;
        inputState.mouseMotionY = 0;
        inputState.endGame = false;
        inputState.leftMouseButtonPressed = false;
        inputState.rightMouseButtonPressed = false;

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                inputState.endGame = true;
            }

            if (event.type == SDL_MOUSEMOTION) {
                inputState.mouseMotionX = event.motion.xrel;
                inputState.mouseMotionY = event.motion.yrel;
                inputState.mousePosX = event.button.x;
                inputState.mousePosY = event.button.y;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    inputState.leftMouseButtonPressed = true;
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    inputState.rightMouseButtonPressed = true;
                }
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

        if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
            inputState.endGame = true;
        }

        if (currentKeyStates[SDL_SCANCODE_W]) {
            inputState.moveForward = true;
        } else {
            inputState.moveForward = false;
        }

        if (currentKeyStates[SDL_SCANCODE_S]) {
            inputState.moveBack = true;
        } else {
            inputState.moveBack = false;
        }

        if (currentKeyStates[SDL_SCANCODE_A]) {
            inputState.moveLeft = true;
        } else {
            inputState.moveLeft = false;
        }

        if (currentKeyStates[SDL_SCANCODE_D]) {
            inputState.moveRight = true;
        } else {
            inputState.moveRight = false;
        }
    }

    void Player::Move(float frameDelta, float speedModifier) {
        if (frameDelta != 0 && speedModifier != 0) {
            const float prevX = camera.pos.x;
            const float prevY = camera.pos.y;

            if (inputState.moveForward != inputState.moveBack) {
                if (inputState.moveForward) {
                    camera.pos += camera.direction * frameDelta * speedModifier;
                }

                if (inputState.moveBack) {
                    camera.pos -= camera.direction * frameDelta * speedModifier;
                }
            }

            if (inputState.moveLeft != inputState.moveRight) {
                if (inputState.moveLeft) {
                    Vec2 moveDirection = {camera.direction.y, -camera.direction.x};
                    moveDirection.Normalize();

                    camera.pos += moveDirection * frameDelta * speedModifier;
                }

                if (inputState.moveRight) {
                    Vec2 moveDirection = {-camera.direction.y, camera.direction.x};
                    moveDirection.Normalize();

                    camera.pos += moveDirection * frameDelta * speedModifier;
                }
            }

            if (level->HasCollided({camera.pos.x, camera.pos.y})) {
                camera.pos.x = prevX;
                camera.pos.y = prevY;
            }
        }
    }

    void Player::Rotate(float frameDelta, float rotationModifier) {
        float rotationAngle = inputState.mouseMotionX * frameDelta * rotationModifier;

        Vec2 oldDirection = camera.direction;
        camera.direction.x = oldDirection.x * cosf(rotationAngle) - oldDirection.y * sinf(rotationAngle);
        camera.direction.y = oldDirection.x * sinf(rotationAngle) + oldDirection.y * cosf(rotationAngle);
        camera.direction.Normalize();

        Vec2 oldPlane = camera.plane;
        camera.plane.x = oldPlane.x * cosf(rotationAngle) - oldPlane.y * sinf(rotationAngle);
        camera.plane.y = oldPlane.x * sinf(rotationAngle) + oldPlane.y * cosf(rotationAngle);
        camera.plane.Normalize();
    }

    bool Player::GameHasEnded() const {
        return inputState.endGame;
    }

    bool Player::InMainMenu() const {
        return inputState.inMainMenu;
    }

    void Player::Update(float frameDelta, float speedModifier, float rotationModifier) {
        UpdateInputState();
        Move(frameDelta, speedModifier);
        Rotate(frameDelta, rotationModifier);
    }

    bool Player::Shoot(std::vector<Enemy>& enemies, float wallDistance) {
        for (Enemy& enemy : enemies) {
            if (enemy.IsVisible() && enemy.pos.Distance(camera.pos) < wallDistance) {
                Vec2 enemyOffsetPos = enemy.pos - camera.pos;
                enemyOffsetPos.Normalize();

                Vec2 camDirection = camera.direction;
                camDirection.Normalize();

                const float scaledThreshold = DOT_PRODUCT_THRESHOLD * (1.0f - (enemy.pos.Distance(camera.pos) / wallDistance));

                if (Vec2::DotProduct(enemyOffsetPos, camera.direction) >= scaledThreshold) {
                    std::cout << "Hit enemy at (" << enemy.pos.x << ", " << enemy.pos.y << ")" << std::endl;
                    enemy.SetVisible(false);
                    return true;
                }
            }
        }

        return false;
    }

    InputState::InputState() {
        moveLeft = false;
        moveRight = false;
        moveForward = false;
        moveBack = false;
        endGame = false;
        inMainMenu = false;
        leftMouseButtonPressed = false;
        rightMouseButtonPressed = false;
        mousePosX = 0;
        mousePosY = 0;
    }
}