#include "stdafx.h"
#include "Octree.h"
#include "Math.h"
#include "Timer.h"

Vec3 RandomVec3(float min, float max) {
    static std::random_device rd;
    static std::mt19937 engine(rd());
    static std::uniform_real_distribution<float> dist(min, max);
    return { dist(engine), dist(engine), dist(engine) };
}

void CreateStaticAABBs(Octree& tree, uint32 counts) {
    for (uint32 i = 0; i < counts; i++) {
        Vec3 center = RandomVec3(-1.f, 1.f);
        Vec3 size = RandomVec3(0.5f, 1.f);

        unique_ptr<AABB> collider = make_unique<AABB>(std::move(center), std::move(size));
        tree.Insert(std::move(*collider.get()));
    }
}

void CreateDynamicAABBs(Octree& tree, uint32 counts) {
    for (uint32 i = 0; i < counts; i++) {
        Vec3 center = RandomVec3(-1.f, 1.f);
        Vec3 size = RandomVec3(0.5f, 1.f);
        Vec3 velocity = RandomVec3(1.f, 3.f);

        unique_ptr<AABB> collider = make_unique<AABB>(std::move(center), std::move(size), std::move(velocity));
        tree.Insert(std::move(*collider.get()));
    }
}

int main() {
    Timer timer;
    Octree tree(2); // MaxDepth = 2
    CreateStaticAABBs(tree, 3);
    CreateDynamicAABBs(tree, 50);

    while (true) {
        timer.UpdateClock();

        tree.Frame();
        tree.PostFrame(timer.DeltaTime());
        tree.Render();

        CreateDynamicAABBs(tree, 1);
        
        timer.DrawTimeInfo();
    }
    
    return 0;
}
