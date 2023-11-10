#pragma once
#include "GameWindow.h"

class D3D11Renderer : public GameWindow
{
public:
    virtual ~D3D11Renderer() = default;

    void                    InitD3D11();
    ComPtr<IDXGISurface1>   GetBackBufferSurface();

protected:
    ComPtr<IDXGISwapChain>          m_SwapChain;
    ComPtr<ID3D11Device>            m_Device;
    ComPtr<ID3D11DeviceContext>     m_ImmediateContext;
    ComPtr<ID3D11RenderTargetView>  m_RenderTargetView;
    ComPtr<ID3D11BlendState>        m_BlendState;
    D3D11_VIEWPORT			        m_ViewPort;
};
