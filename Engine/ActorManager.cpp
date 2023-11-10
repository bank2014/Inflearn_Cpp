#include "pch.h"
#include "ActorManager.h"

void ActorManager::UpdateAllBeginPlays()
{
    auto range = m_Actors.equal_range(m_CurrentScene);
    for (auto& it = range.first; it != range.second; ++it)
    {
        it->second->SetDevice(m_Device);
        it->second->SetDeviceContext(m_ImmediateContext);
        it->second->BeginPlay();
    }
}

void ActorManager::UpdateAllTicks(float deltaTime)
{
    auto range = m_Actors.equal_range(m_CurrentScene);
    for (auto& it = range.first; it != range.second; ++it)
    {
        it->second->Tick(deltaTime);
    }

}

void ActorManager::RenderActors()
{
    auto range = m_Actors.equal_range(m_CurrentScene);
    for (auto& it = range.first; it != range.second; ++it)
    {
        it->second->Render();
    }
}

void ActorManager::RegisterActor(unique_ptr<UPrimitiveComponent> actor)
{
    m_Actors.insert(std::make_pair(actor->m_CurrentSceneID, std::move(actor)));
}

void ActorManager::DeleteActor(int id)
{
    m_Actors.erase(id);
}
