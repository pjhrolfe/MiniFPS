#include "Vector.h"

namespace MiniFPS
{
    Vec2::Vec2() : x(0), y(0)
    {}

    Vec2::Vec2(const float x, const float y) : x(x), y(y)
    {}

    Vec2::Vec2(const FloatPoint point) : x(point.x), y(point.y)
    {}

    Vec2::Vec2(const Vec2Int &intVector) : x(static_cast<float>(intVector.x)), y(static_cast<float>(intVector.y))
    {}

    Vec2::Vec2(const Vec2 &floatVector) : x(floatVector.x), y(floatVector.y)
    {}

    float Vec2::Length()
    {
        return sqrt((x * x) + (y * y));
    }

    float Vec2::Distance(const Vec2 &otherVector) const
    {
        return sqrtf(powf(x - otherVector.x, 2) + powf(y - otherVector.y, 2));
    }


    float Vec2::DotProduct(const Vec2 &v1, const Vec2 &v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y);
    }

    void Vec2::Normalize()
    {
        const float length = Length();
        x = x / length;
        y = y / length;
    }

    Vec2 &Vec2::operator=(const Vec2 &otherVector)
    {
        if (this != &otherVector)
        {
            x = otherVector.x;
            y = otherVector.y;
        }
        return *this;
    }

    Vec2 Vec2::operator+(const Vec2 &otherVector)
    {
        return {x + otherVector.x, y + otherVector.y};
    }

    Vec2 &Vec2::operator+=(const Vec2 &otherVector)
    {
        x += otherVector.x;
        y += otherVector.y;
        return *this;
    }

    Vec2 Vec2::operator-(const Vec2 &otherVector)
    {
        return {x - otherVector.x, y - otherVector.y};
    }

    Vec2 &Vec2::operator-=(const Vec2 &otherVector)
    {
        x -= otherVector.x;
        y -= otherVector.y;
        return *this;
    }

    Vec2 Vec2::operator*(const float value)
    {
        return {x * value, y * value};
    }

    float Vec2::operator*(const Vec2 &otherVector)
    {
        return (x * otherVector.y - y * otherVector.x);
    }

    Vec2Int::Vec2Int() : x(0), y(0)
    {}

    Vec2Int::Vec2Int(int x, int y) : x(x), y(y)
    {}

    Vec2Int::Vec2Int(IntPoint point) : x(point.x), y(point.y)
    {}

    Vec2Int::Vec2Int(const Vec2 &floatVector) : x(static_cast<int>(floatVector.x)), y(static_cast<float>(floatVector.y))
    {}

    Vec2Int::Vec2Int(const Vec2Int &vector) : x(vector.x), y(vector.y)
    {}

    Vec2Int Vec2Int::operator+(const Vec2Int &otherVector)
    {
        return Vec2Int(x + otherVector.x, y + otherVector.y);
    }

    Vec2Int Vec2Int::operator-(const Vec2Int &otherVector)
    {
        return Vec2Int(x - otherVector.x, y - otherVector.y);
    }
}