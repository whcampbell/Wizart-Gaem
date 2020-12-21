#pragma once

/**
 * struct representing any two dimensional position or transformation
 */ 
struct Vector2 {
    float x, y;

    Vector2() : x(0), y(0) {}
    Vector2(int x, int y) : x(x), y(y) {}

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

/**
 * struct representing any three dimensional position or transformation.
 * the ^ operator is overloaded to act as the cross product between
 * two Vector3 objects
 */
struct Vector3 {
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(int x, int y, int z) : x(x), y(y), z(z) {}

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

/**
 * struct representing any four dimensional position or transformation
 */
struct Vector4 {
    float x, y, z, w;

    Vector4() : x(0), y(0), z(0), w(0) {}
    Vector4(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {}

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