#pragma once
#include "Math.h"

// 현재 모든 물리량이 AABB에 종속됨
struct AABB {
    Vec3 Center{ 0.f,0.f,0.f };
    Vec3 Size{ 0.f,0.f,0.f };
    Vec3 Velocity{ 0.f,0.f,0.f };

    AABB() {};

    // dynamic AABB 초기화용
    AABB(Vec3& center, Vec3& size, Vec3& velocity) :
        Center(center),
        Size(size),
        Velocity(velocity) {}
    AABB(Vec3&& center, Vec3&& size, Vec3&& velocity) :
        Center(std::move(center)),
        Size(std::move(size)), 
        Velocity(std::move(velocity)) {}

    // Static AABB 초기화용
    AABB(Vec3& center, Vec3& size) :
        Center(center),
        Size(size) {}
    AABB(Vec3&& center, Vec3&& size) :
        Center(std::move(center)),
        Size(std::move(size)) {}

    ~AABB() = default;

    void Move(float deltaTime) {
        Center += (Velocity * deltaTime);
       
        if (Center.X - Size.X * 0.5f < -1.f || Center.X + Size.X * 0.5f > 1.f) {
            Velocity.X *= -1.f;
        }
        if (Center.Y - Size.Y * 0.5f < -1.f || Center.Y + Size.Y * 0.5f > 1.f) {
            Velocity.Y *= -1.f;
        }
        if (Center.Z - Size.Z * 0.5f < -1.f || Center.Z + Size.Z * 0.5f > 1.f) {
            Velocity.Z *= -1.f;
        }
    }

    // AABB의 8개의 꼭지점
    inline Vec3 LeftUpFront() const {
        return { Center.X - Size.X * 0.5f, Center.Y + Size.Y * 0.5f, Center.Z - Size.Z * 0.5f };
    }
    inline Vec3 RightUpFront() const {
        return { Center.X + Size.X * 0.5f, Center.Y + Size.Y * 0.5f, Center.Z - Size.Z * 0.5f };
    }
    inline Vec3 LeftDownFront() const {
        return { Center.X - Size.X * 0.5f, Center.Y - Size.Y * 0.5f, Center.Z - Size.Z * 0.5f };
    }
    inline Vec3 RightDownFront() const {
        return { Center.X + Size.X * 0.5f, Center.Y - Size.Y * 0.5f, Center.Z - Size.Z * 0.5f };
    }
    inline Vec3 LeftUpBack() const {
        return { Center.X - Size.X * 0.5f, Center.Y + Size.Y * 0.5f, Center.Z + Size.Z * 0.5f };
    }
    inline Vec3 RightUpBack() const {
        return { Center.X + Size.X * 0.5f, Center.Y + Size.Y * 0.5f, Center.Z + Size.Z * 0.5f };
    }
    inline Vec3 LeftDownBack() const {
        return { Center.X - Size.X * 0.5f, Center.Y - Size.Y * 0.5f, Center.Z + Size.Z * 0.5f };
    }
    inline Vec3 RightDownBack() const {
        return { Center.X + Size.X * 0.5f, Center.Y - Size.Y * 0.5f, Center.Z + Size.Z * 0.5f };
    }
};

struct Point {
    Vec3 Center = { 0.f,0.f,0.f };

    Point() = delete;
    Point(Vec3& center) : Center(center) {}
    Point(Vec3&& center) : Center(std::move(center)) {}
    ~Point() = default;
};
