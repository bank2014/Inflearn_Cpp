#include "stdafx.h"
#include "CollisionSolver.h"

CollisionType CollisionSolver::AABB2AABB(AABB& a, AABB& b)
{
    uint32 collision = 1;
    if (a.RightUpBack().X >= b.LeftDownFront().X || a.LeftDownFront().X <= b.RightUpBack().X) collision <<= 1;
    if (a.RightUpBack().Y >= b.LeftDownFront().Y || a.LeftDownFront().Y <= b.RightUpBack().Y) collision <<= 1;
    if (a.RightUpBack().Z >= b.LeftDownFront().Z || a.LeftDownFront().Z <= b.RightUpBack().Z) collision <<= 1;

    if (collision == 0b000'0001) return CollisionType::None;
    else if (collision == 0b000'1000) return CollisionType::Full;
    else return CollisionType::Partial;
}

CollisionType CollisionSolver::Point2AABB(Point& a, AABB& b)
{
    if (a.Center.X <= b.LeftDownFront().X || a.Center.X >= b.RightUpBack().X) return CollisionType::None;
    if (a.Center.Y <= b.LeftDownFront().Y || a.Center.Y >= b.RightUpBack().Y) return CollisionType::None;
    if (a.Center.Z <= b.LeftDownFront().Z || a.Center.Z >= b.RightUpBack().Z) return CollisionType::None;
    return CollisionType::Full;

}
