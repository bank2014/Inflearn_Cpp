#include "pch.h"
#include "D3D11Renderer.h"

void D3D11Renderer::InitD3D11()
{
    // 디바이스 & swap chain 생성
    DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
    SwapChainDesc.BufferDesc.Width = m_WindowWidth;
    SwapChainDesc.BufferDesc.Height = m_WindowHeight;
    SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    SwapChainDesc.SampleDesc.Count = 1;
    SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    SwapChainDesc.BufferCount = 1;
    SwapChainDesc.OutputWindow = m_hWnd;
    SwapChainDesc.Windowed = true;
    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;
    UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
    D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        NULL,
        DriverType,
        NULL,
        Flags,
        &pFeatureLevels,
        1,
        D3D11_SDK_VERSION,
        &SwapChainDesc,
        m_SwapChain.GetAddressOf(),
        m_Device.GetAddressOf(),
        NULL,
        m_ImmediateContext.GetAddressOf());
    ASSERT_HR(hr);

    // 렌더타겟 생성
    ComPtr<ID3D11Texture2D> BackBuffer;
    hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)BackBuffer.GetAddressOf());
    hr = m_Device->CreateRenderTargetView(BackBuffer.Get(), NULL, m_RenderTargetView.GetAddressOf());
    ASSERT_HR(hr);
    m_ImmediateContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), NULL);

    // 뷰포트 설정
    m_ViewPort.Width = m_WindowWidth;
    m_ViewPort.Height = m_WindowHeight;
    m_ViewPort.MinDepth = 0.0f; //ndc의 depth clipping range를 의미: 0~1
    m_ViewPort.MaxDepth = 1.0f;
    m_ViewPort.TopLeftX = 0;
    m_ViewPort.TopLeftY = 0;
    m_ImmediateContext->RSSetViewports(1, &m_ViewPort);

    // 블렌드 스테이트 설정
    D3D11_BLEND_DESC bsd{};
    bsd.RenderTarget[0].BlendEnable = true;
    bsd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    bsd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bsd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bsd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    bsd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bsd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bsd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    m_Device->CreateBlendState(&bsd, m_BlendState.GetAddressOf());
}

ComPtr<IDXGISurface1> D3D11Renderer::GetBackBufferSurface()
{
    ComPtr<IDXGISurface1> BackBuffer;
    HRESULT hr = m_SwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (LPVOID*)BackBuffer.GetAddressOf());
    ASSERT_HR(hr);
    return BackBuffer;
}

