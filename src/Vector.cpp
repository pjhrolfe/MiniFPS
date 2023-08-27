#include <cmath>

#include "Vector.h"

namespace MiniFPS {
    FloatVector2::FloatVector2() : x(0), y(0) {}

    FloatVector2::FloatVector2(const float x, const float y) : x(x), y(y) {}

    FloatVector2::FloatVector2(const FloatPoint point) : x(point.x), y(point.y) {}

    FloatVector2::FloatVector2(const IntVector2& intVector) : x(static_cast<float>(intVector.x)), y(static_cast<float>(intVector.y)) {}

    FloatVector2::FloatVector2(const FloatVector2& floatVector) : x(floatVector.x), y(floatVector.y) {}

    float FloatVector2::Length() {
        return sqrt((x*x) + (y*y));
    }

    void FloatVector2::Normalize() {
        const float length = Length();
        x = x / length;
        y = y / length;
    }

    FloatVector2 FloatVector2::operator+(const FloatVector2& otherVector) {
        return {x + otherVector.x, y + otherVector.y};
    }

    FloatVector2 FloatVector2::operator-(const FloatVector2& otherVector) {
        return {x - otherVector.x, y - otherVector.y};
    }

    FloatVector2 FloatVector2::operator* (const float value) {
        return {x * value, y * value};
    }

    DoubleVector2::DoubleVector2() : x(0), y(0) {}

    DoubleVector2::DoubleVector2(const double x, const double y) : x(x), y(y) {}

    DoubleVector2::DoubleVector2(const FloatPoint point) : x(point.x), y(point.y) {}

    DoubleVector2::DoubleVector2(const IntVector2& intVector) : x(static_cast<double >(intVector.x)), y(static_cast<double >(intVector.y)) {}

    DoubleVector2::DoubleVector2(const DoubleVector2& doubleVector) : x(doubleVector.x), y(doubleVector.y) {}

    double DoubleVector2::Length() {
        return sqrt((x*x) + (y*y));
    }

    void DoubleVector2::Normalize() {
        const double length = Length();
        x = x / length;
        y = y / length;
    }

    DoubleVector2 DoubleVector2::operator+(const DoubleVector2& otherVector) {
        return {x + otherVector.x, y + otherVector.y};
    }

    DoubleVector2 DoubleVector2::operator-(const DoubleVector2& otherVector) {
        return {x - otherVector.x, y - otherVector.y};
    }

    DoubleVector2 DoubleVector2::operator* (const double value) {
        return {x * value, y * value};
    }

    IntVector2::IntVector2() : x(0), y(0) {}

    IntVector2::IntVector2(int x, int y) : x(x), y(y) {}

    IntVector2::IntVector2(IntPoint point) : x(point.x), y(point.y) {}

    IntVector2::IntVector2(const FloatVector2 &floatVector) : x(static_cast<int>(floatVector.x)), y(static_cast<float>(floatVector.y)) {}

    IntVector2::IntVector2(const DoubleVector2 &doubleVector) : x(static_cast<int>(doubleVector.x)), y(static_cast<float>(doubleVector.y)) {}

    IntVector2::IntVector2(const IntVector2 &vector) : x(vector.x), y(vector.y) {}

    IntVector2 IntVector2::operator+(const IntVector2 &otherVector) {
        return IntVector2(x + otherVector.x, y + otherVector.y);
    }

    IntVector2 IntVector2::operator-(const IntVector2 &otherVector) {
        return IntVector2(x - otherVector.x, y - otherVector.y);
    }
}