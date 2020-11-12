#pragma once


struct Vector2 {
    float x, y;

    Vector2 operator+(const Vector2& v) {
        Vector2 vec = *this;
        vec.x += v.x;
        vec.y += v.y;
        return vec;
    }

    void operator+=(const Vector2& v) {
        this->x += v.x;
        this->y += v.y;
    }

    
    Vector2 operator-(const Vector2& v) {
        Vector2 vec = *this;
        vec.x -= v.x;
        vec.y -= v.y;
        return vec;
    }

    void operator-=(const Vector2& v) {
        this->x -= v.x;
        this->y -= v.y;
    }
};

struct Vector3 {
    float x, y, z;

    Vector3 operator+(const Vector2& v) {
        Vector3 vec = *this;
        vec.x += v.x;
        vec.y += v.y;
        return vec;
    }

    void operator+=(const Vector2& v) {
        this->x += v.x;
        this->y += v.y;
    }

    
    Vector3 operator-(const Vector2& v) {
        Vector3 vec = *this;
        vec.x -= v.x;
        vec.y -= v.y;
        return vec;
    }

    void operator-=(const Vector2& v) {
        this->x -= v.x;
        this->y -= v.y;
    }

    Vector3 operator+(const Vector3& v) {
        Vector3 vec = *this;
        vec.x += v.x;
        vec.y += v.y;
        vec.z += v.z;
        return vec;
    }

    void operator+=(const Vector3& v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
    }

    
    Vector3 operator-(const Vector3& v) {
        Vector3 vec = *this;
        vec.x -= v.x;
        vec.y -= v.y;
        vec.z -= v.z;
        return vec;
    }

    void operator-=(const Vector3& v) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
    }

    Vector3 operator^(const Vector3& v) {
        Vector3 vec;
        vec.x = this->y * v.z - this->z * v.y;
        vec.y = this->z * v.x - this->x * v.z;
        vec.z = this->x * v.y - this->y * v.x;
        return vec;
    }
};

struct Vector4 {
    float x, y, z, w;

    Vector4 operator+(const Vector2& v) {
        Vector4 vec = *this;
        vec.x += v.x;
        vec.y += v.y;
        return vec;
    }

    void operator+=(const Vector2& v) {
        this->x += v.x;
        this->y += v.y;
    }

    
    Vector4 operator-(const Vector2& v) {
        Vector4 vec = *this;
        vec.x -= v.x;
        vec.y -= v.y;
        return vec;
    }

    void operator-=(const Vector2& v) {
        this->x -= v.x;
        this->y -= v.y;
    }

    Vector4 operator+(const Vector3& v) {
        Vector4 vec = *this;
        vec.x += v.x;
        vec.y += v.y;
        vec.z += v.z;
        return vec;
    }

    void operator+=(const Vector3& v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
    }

    
    Vector4 operator-(const Vector3& v) {
        Vector4 vec = *this;
        vec.x -= v.x;
        vec.y -= v.y;
        vec.z -= v.z;
        return vec;
    }

    void operator-=(const Vector3& v) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
    }

    Vector4 operator+(const Vector4& v) {
        Vector4 vec = *this;
        vec.x += v.x;
        vec.y += v.y;
        vec.z += v.z;
        vec.w += v.w;
        return vec;
    }

    void operator+=(const Vector4& v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        this->w += v.w;
    }

    
    Vector4 operator-(const Vector4& v) {
        Vector4 vec = *this;
        vec.x -= v.x;
        vec.y -= v.y;
        vec.z -= v.z;
        vec.w -= v.w;
        return vec;
    }

    void operator-=(const Vector4& v) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        this->w -= v.w;
    }
};