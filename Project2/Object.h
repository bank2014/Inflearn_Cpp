#pragma once
#include "Collider.h"

class GameObject {
public:
    AABB* Collider = nullptr;

    GameObject() {}
    GameObject(AABB*& collider) : Collider(collider) {}
    virtual ~GameObject() = default;
};