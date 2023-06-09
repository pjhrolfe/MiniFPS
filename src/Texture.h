#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Camera.h"
#include "Level.h"
#include "Menu.h"

namespace MiniFPS {
    struct Texture {
        Texture();

        Texture(std::string name, std::string filePath);

        string name;
        Uint32** buffer;
        size_t size;
    };
}