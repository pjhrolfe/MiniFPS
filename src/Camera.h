#pragma once

#include "Common.h"
#include "Vector.h"

namespace MiniFPS
{
    const Vec2Int CAMERA_RESOLUTION {512, 288};

    struct Camera
    {
    public:
        Camera();

        Camera(float _x, float _y, float _angle, float _horizontalFieldOfView, int viewportWidth, int viewportHeight,
               size_t maxRenderDistance);

        static float CalculateAspectRatio(size_t width, size_t height);

        // Position relative to level cells (where x=0, y=0 would be the top-left corner of the level)
        Vec2 pos;
        // Horizontal field of view in radians
        float horizontalFieldOfView;

        Vec2 direction;
        Vec2 plane;

        // Size of viewport in pixels
        int viewportWidth, viewportHeight;
        // Max distance for raycasts
        size_t maxRenderDistance;
    };
}

