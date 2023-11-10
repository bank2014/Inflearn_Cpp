#include "pch.h"
#include "Core.h"

bool  EngineCore::EngineFrame()
{
    TIMER.UpdateClock();
    INPUT_HANDLER.UpdateKeyEvent(m_hWnd);
    //AUDIO_MANAGER.UpdateAudioFrame();
    ACTOR_MANAGER.UpdateAllTicks(TIMER.DeltaTime());

    return true;
}

bool  EngineCore::EngineRender()
{
    // PRE RENDER
    const float color[4] = { 0.1f,0.1f,0.1f, 1.f };
    m_ImmediateContext->ClearRenderTargetView(m_RenderTargetView.Get(), color);
    m_ImmediateContext->OMSetBlendState(m_BlendState.Get(), color, -1);

    // RENDER
    ACTOR_MANAGER.RenderActors();
    TIMER.DrawTimeInfo();

    // POST RENDER
    TEXT_MANAGER.RenderTexts();
    m_SwapChain->Present(0,0);

    return true;
}

void EngineCore::Init()
{
    InitD3D11();
    TEXT_MANAGER.InitDWrite(GetBackBufferSurface(), m_hWnd, 17.f, L"¸¼Àº °íµñ");
    TEXTURE_MANAGER.SetDevice(m_Device);
    SHADER_MANAGER.SetDevice(m_Device);
    ACTOR_MANAGER.SetDeviceAndContext(m_Device, m_ImmediateContext);
}

void EngineCore::RegisterActor(std::unique_ptr<UPrimitiveComponent> actor)
{
    ACTOR_MANAGER.RegisterActor(std::move(actor));
}

void EngineCore::Run()
{
    MSG msg{};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            if (!EngineFrame() || !EngineRender())
            {
                break;
            }
        }
    }
}
