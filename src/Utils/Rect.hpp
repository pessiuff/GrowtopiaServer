#pragma once
#include <utility>

typedef struct _CL_Rectf {
    float x;
    float y;
    float width;
    float height;

    _CL_Rectf() {
        x = 0.0f;
        y = 0.0f;
        width = 0.0f;
        height = 0.0f;
    }

    _CL_Rectf(float f) {
        x = f;
        y = f;
        width = f;
        height = f;
    }

    _CL_Rectf(float x, float y, float width, float height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    bool operator==(const _CL_Rectf& other) const {
        return x == other.x && y == other.y && width == other.width && height == other.height;
    }

    bool operator!=(const _CL_Rectf& other) const {
        return x != other.x || y != other.y || width != other.width || height != other.height;
    }

    _CL_Rectf operator+(const _CL_Rectf& other) const {
        return _CL_Rectf(x + other.x, y + other.y, width + other.width, height + other.height);
    }

    _CL_Rectf operator-(const _CL_Rectf& other) const {
        return _CL_Rectf(x - other.x, y - other.y, width - other.width, height - other.height);
    }

    _CL_Rectf operator*(const float& other) const {
        return _CL_Rectf(x * other, y * other, width * other, height * other);
    }
} CL_Rectf;

typedef struct _CL_Recti {
    int x;
    int y;
    int width;
    int height;

    _CL_Recti() {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }

    _CL_Recti(int f) {
        x = f;
        y = f;
        width = f;
        height = f;
    }

    _CL_Recti(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    bool operator==(const _CL_Recti& other) const {
        return x == other.x && y == other.y && width == other.width && height == other.height;
    }

    bool operator!=(const _CL_Recti& other) const {
        return x != other.x || y != other.y || width != other.width || height != other.height;
    }

    _CL_Recti operator+(const _CL_Recti& other) const {
        return _CL_Recti(x + other.x, y + other.y, width + other.width, height + other.height);
    }

    _CL_Recti operator-(const _CL_Recti& other) const {
        return _CL_Recti(x - other.x, y - other.y, width - other.width, height - other.height);
    }

    _CL_Recti operator*(const int& other) const {
        return _CL_Recti(x * other, y * other, width * other, height * other);
    }
} CL_Recti;