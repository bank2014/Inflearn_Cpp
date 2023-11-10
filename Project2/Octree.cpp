#include "stdafx.h"
#include "Octree.h"

Octree::Octree(uint16 MaxDepth, AABB&& rootVolume) :
    MaxDepth(MaxDepth),
    RootVolume(std::move(rootVolume))
{
    NodeAABBs.resize(GetTotalNodeCount());
    NodeAABBs[0] = RootVolume;
    CreateAllNodeAABB(std::move(RootVolume), 0, 0);
}

void Octree::Insert(AABB&& obj)
{
    Insert(std::move(obj), 0, 0, 0, RootVolume);
    // �浹 �˻縦 ���� Wrappers�� NodeIndex ������ �����Ѵ�
    std::sort(
        Wrappers.begin(),
        Wrappers.end(),
        [](const Wrapper& lhs, const Wrapper& rhs) {return lhs.NodeIndex < rhs.NodeIndex; });
}

void Octree::Frame()
{
    uint16 currentDepth = Wrappers.back().Depth;
    for (uint32 pivot = Wrappers.size() - 1; pivot != static_cast<uint32>(-1); --pivot) {
        if (currentDepth != Wrappers[pivot].Depth) {
            --currentDepth;
            //pivot�� ���� wrapper�� ��� depth�� 1 ���ҽ�Ų��
            //pivot�� ���� wrapper�� ��� �θ� ���� ���� : nodeIndex = (nodeIndex - 1) / 8
            for (uint32 i = pivot + 1; i < Wrappers.size(); ++i) {
                Wrappers[i].Depth--;
                Wrappers[i].NodeIndex = (Wrappers[i].NodeIndex - 1) / 8;
            }
        }
        if (Wrappers[pivot].bIsStatic) continue;

        for (uint32 index = Wrappers.size() - 1; index != static_cast<uint32>(-1); --index) {
            if (&Wrappers[pivot] == &Wrappers[index]) continue;
            if (Wrappers[pivot].NodeIndex != Wrappers[index].NodeIndex) {
                if (index < pivot) continue;
                else if(index > pivot) break;
            }

            if (CollisionSolver::AABB2AABB(Wrappers[pivot].Collider, Wrappers[index].Collider) >= CollisionType::Partial) {
                Wrappers[pivot].bCollided = true;
                Wrappers[index].bCollided = true;
            }
        }
    }

    // bCollided = true �� �͵��� Wrappers �ڿ������� �����
    Wrappers.erase(
        std::remove_if(Wrappers.begin(),Wrappers.end(), [](const Wrapper& wrapper) {return wrapper.bCollided; }),
        Wrappers.end());
}

void Octree::PostFrame(float deltaTime)
{
    std::vector<AABB> temp;

    for (uint32 i = 0; i < Wrappers.size(); ++i) {
        if (Wrappers[i].bIsStatic) continue;
        temp.push_back(std::move(Wrappers[i].Collider));
        Wrappers.erase(Wrappers.begin() + i);
    }
    for (auto& i : temp) {
        i.Move(deltaTime);
        Insert(std::move(i));
    }
}

void Octree::Render()
{
    for (int32 i = 0; i < Wrappers.size(); ++i) {
        Wrappers[i].Print();
    }
}

void Octree::Insert(AABB&& obj, uint32 nodeIndex, uint32 parentNodeIndex, uint16 depth, const AABB& nodeAABB)
{
    if (depth == MaxDepth) { // leaf���� ���� �浹�� ��� �׳� leaf�� �ְ� ������
        bool isStatic = obj.Velocity.IsZeroVector() ? true : false;
        Wrappers.emplace_back(Wrapper(std::move(obj), nodeIndex, parentNodeIndex, depth, isStatic));
        return;
    }
    // obj�� center�� ��� child�� ���ϴ��� ã�´� (������ġ�� ��� ����/��/�� child�� ����)
    int32 whichChild = 0;
    if (obj.Center.X > nodeAABB.Center.X) whichChild |= 1;
    if (obj.Center.Y < nodeAABB.Center.Y) whichChild |= 2;
    if (obj.Center.Z > nodeAABB.Center.Z) whichChild |= 4;
    uint32 childNodeIndex = 8 * nodeIndex + 1 + whichChild;
    // obj�� center�� ���� child�� AABB�� �浹 �˻�
    CollisionType result = CollisionSolver::AABB2AABB(obj, NodeAABBs[childNodeIndex]);

    // �κ� �浹�� child�� ���� �ʰ� ���� ��忡 �ִ´�
    if (result == CollisionType::Partial) {
        bool isStatic = obj.Velocity.IsZeroVector() ? true : false;
        Wrappers.emplace_back(Wrapper(std::move(obj), nodeIndex, parentNodeIndex, depth, isStatic));
    }
    // ���� �浹�� child�� insert
    else if (result == CollisionType::Full) 
        Insert(std::move(obj), childNodeIndex, nodeIndex, depth + 1, NodeAABBs[childNodeIndex]);
    // ������ �߻��� ��� (result == CollisionType::None)
    else
        assert(true);
}

void Octree::CreateAllNodeAABB(const AABB&& volume, uint32 parentNodeIndex, uint16 depth)
{
    if (depth == MaxDepth) return;

    /*  �Ⱥи� ����
        ��     ��
        0 1   4 5
        2 3   6 7  */
    for (uint32 whichChild = 0; whichChild < 8; ++whichChild)
    {
        uint32 childNodeIndex = 8 * parentNodeIndex + 1 + whichChild;
        Vec3 childSize = volume.Size / 2.f;
        Vec3 childCenter = volume.Center - (childSize / 2.f);
        childCenter.Y = -childCenter.Y; // y���� �ݴ�� ������ 0�� child�� �������� �Ѵ�
        if (whichChild & 1)  childCenter.X += childSize.X;
        if (whichChild & 2)  childCenter.Y -= childSize.Y;
        if (whichChild & 4)  childCenter.Z += childSize.Z;

        NodeAABBs[childNodeIndex] = AABB(childCenter, childSize);
        CreateAllNodeAABB(AABB(childCenter, childSize), childNodeIndex, depth + 1);
    }
}

uint32 Octree::GetTotalNodeCount() const
{
    uint32 totalNode = 1;
    for (uint32 i = MaxDepth; i != 0; --i) {
        totalNode += static_cast<uint32>(std::pow(8, i));
    }
    return totalNode;
}
