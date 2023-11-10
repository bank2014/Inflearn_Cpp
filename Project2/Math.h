#pragma once

// 전역 상수
constexpr float PI{ 3.141592f };
constexpr float EPSILON{ 0.0001f };
constexpr float MAX_FLOAT{ std::numeric_limits<float>::max() };

struct Float3 {
    union {
        float Axis[3];
        struct {
            float X, Y, Z;
        };
    };
};

struct Float4 {
    union {
        float Axis[4];
        struct {
            float X, Y, Z, W;
        };
    };
};

struct Vec3 : public Float3 {
    Vec3() = default;
    Vec3(float x, float y, float z) : Float3{x,y,z} {}
    ~Vec3() = default;

    inline void Set(Vec3& vec) {
        *this = vec;
    }
    inline void Set(Vec3&& vec) {
        *this = std::move(vec);
    }

    inline Vec3& operator=(const Vec3& _vec) {
        if (this != &_vec) {
            X = _vec.X;
            Y = _vec.Y;
            Z = _vec.Z;
        }
        return *this;
    }
    inline bool operator==(const Vec3& _vec) const {
        return X == _vec.X && Y == _vec.Y && Z == _vec.Z;
    }

    inline Vec3 operator+(const Vec3& _vec) const {
        return { X + _vec.X, Y + _vec.Y, Z + _vec.Z };
    }
    inline Vec3 operator-(const Vec3& _vec) const {
        return { X - _vec.X, Y - _vec.Y, Z - _vec.Z };
    }
    inline Vec3 operator*(const float f) const {
        return { X * f, Y * f, Z * f };
    }
    inline Vec3 operator/(const float f) const {
        const float ratio = 1.f / f;
        return { X * ratio, Y * ratio, Z * ratio };
    }

    inline Vec3 operator+=(const Vec3& _vec) {
        return { X += _vec.X, Y += _vec.Y, Z += _vec.Z };
    }
    inline Vec3 operator-=(const Vec3& _vec) {
        return { X -= _vec.X, Y -= _vec.Y, Z -= _vec.Z };
    }

    inline float operator |(const Vec3& _vec) { // Dot product
        return X * _vec.X + Y * _vec.Y + Z * _vec.Z;
    }
    inline Vec3 operator ^(const Vec3& _vec) { // Cross product
        return { Y * _vec.Z - Z * _vec.Y, Z * _vec.X - X * _vec.Z, X * _vec.Y - Y * _vec.X };
    }
    inline float Length() const {
        return sqrt(X * X + Y * Y + Z * Z);
    }
    inline Vec3 Normalize() const {
        const float ratio = 1.f / Length();
        return { X * ratio, Y * ratio, Z * ratio };
    }
    inline bool IsZeroVector() const {
        return X == 0.f && Y == 0.f && Z == 0.f;
    }
};