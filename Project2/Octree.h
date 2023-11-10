#pragma once
#include "Math.h"
#include "Object.h"
#include "CollisionSolver.h"

struct Wrapper {
    AABB Collider;
    uint32 NodeIndex = 0;
    uint32 ParentNodeIndex = 0;
    uint16 Depth = 0;
    bool bCollided = false;
    bool bIsStatic = false;

    Wrapper() = delete;
    Wrapper(AABB&& collider, uint32 nodeIndex, uint32 parentNodeIndex, uint16 depth, bool isStatic = false) :
        Collider(std::move(Collider)),
        NodeIndex(nodeIndex),
        ParentNodeIndex(parentNodeIndex),
        Depth(depth),
        bIsStatic(isStatic) {}

    void Print() const {
        printf("Depth %d, NodeIndex %d, isStatic: %s, Collider: %p\n", Depth, NodeIndex, bIsStatic ? "true" : "false", &Collider);
    }
};

class Octree {
public:
    std::vector<Wrapper> Wrappers;
private:
    uint32 MaxDepth;
    AABB RootVolume;
    std::vector<AABB> NodeAABBs;

public:
    Octree() = delete;
    Octree(uint16 MaxDepth, AABB&& rootVolume = { Vec3(0,0,0),Vec3(2,2,2) });
    
    void Insert(AABB&& obj);
    void Frame();
    void PostFrame(float deltaTime);
    void Render();

private:
    void Insert(AABB&& obj, uint32 nodeIndex, uint32 parentNode, uint16 depth, const AABB& nodeAABB);
    void CreateAllNodeAABB(const AABB&& volume, uint32 NodeIndex, uint16 depth);
    uint32 GetTotalNodeCount() const;
};

