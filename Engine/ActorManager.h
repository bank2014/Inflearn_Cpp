#pragma once
#include "AActor.h"

class ActorManager
{
public:
    void SetDeviceAndContext(ComPtr<ID3D11Device>& device, ComPtr<ID3D11DeviceContext>& context) { 
        m_Device = device; 
        m_ImmediateContext = context;
    }
    void UpdateAllBeginPlays();
    void UpdateAllTicks(float deltaTime);
    void RenderActors();
    void RegisterActor(unique_ptr<UPrimitiveComponent> actor);
    void DeleteActor(int id);

    static ActorManager& Get() {
        static ActorManager Instance;
        return Instance;
    }
private:
    ActorManager() : m_CurrentScene(0) {}
    ~ActorManager() { m_Actors.clear(); }
    
    ComPtr<ID3D11Device> m_Device;
    ComPtr<ID3D11DeviceContext> m_ImmediateContext;
    std::multimap<int, unique_ptr<UPrimitiveComponent>> m_Actors; // current scene id | actor
    int m_CurrentScene;
};
#define ACTOR_MANAGER ActorManager::Get()
inline ActorManager& GetActorManager() { return ActorManager::Get(); }