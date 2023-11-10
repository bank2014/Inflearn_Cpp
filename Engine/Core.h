#pragma once
#include "D3D11Renderer.h"
#include "Timer.h"
#include "InputHandler.h"
#include "TextManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "ActorManager.h"

class EngineCore : public D3D11Renderer
{
private:
    bool  EngineFrame();
    bool  EngineRender();

public:
    void Init();
    void RegisterActor(std::unique_ptr<UPrimitiveComponent> actor);
    void Run();
};
