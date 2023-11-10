#pragma once
#include "Collider.h"

struct CollisionSolver {
    static CollisionType AABB2AABB(AABB& a, AABB& b);
    static CollisionType Point2AABB(Point& a, AABB& b);
};
