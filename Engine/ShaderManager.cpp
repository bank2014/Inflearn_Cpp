#include "pch.h"
#include "ShaderManager.h"

VertexShaderInfo ShaderManager::GetVertexShader(const std::wstring& filename)
{
    auto iter = m_VertexShaders.find(filename);
    if (iter != m_VertexShaders.end())
    {
        return iter->second;
    }

    HRESULT hr = S_OK;
    ComPtr<ID3DBlob> ErrorCode;
    ComPtr<ID3DBlob> VertexShaderCode;
    ComPtr<ID3D11VertexShader> VertexShader;
    VertexShaderInfo vsInfo;

    hr = D3DCompileFromFile(filename.c_str(), nullptr, nullptr, "VS", "vs_5_0", 0, 0, VertexShaderCode.GetAddressOf(), ErrorCode.GetAddressOf());
    ASSERT_HR(hr);

    hr = m_Device->CreateVertexShader(VertexShaderCode->GetBufferPointer(), VertexShaderCode->GetBufferSize(), nullptr, VertexShader.GetAddressOf());
    ASSERT_HR(hr);

    vsInfo.code = std::move(VertexShaderCode);
    vsInfo.shader = std::move(VertexShader);

    m_VertexShaders.insert(std::make_pair(filename, vsInfo));
    return m_VertexShaders[filename];
}

PixelShaderInfo ShaderManager::GetPixelShader(const std::wstring& filename)
{
    auto iter = m_PixelShaders.find(filename);
    if (iter != m_PixelShaders.end())
    {
        return iter->second;
    }

    HRESULT hr = S_OK;
    ComPtr<ID3DBlob> ErrorCode;
    ComPtr<ID3DBlob> PixelShaderCode;
    ComPtr<ID3D11PixelShader> PixelShader;
    PixelShaderInfo psInfo;

    hr = D3DCompileFromFile(filename.c_str(), nullptr, nullptr, "PS", "ps_5_0", 0, 0, PixelShaderCode.GetAddressOf(), ErrorCode.GetAddressOf());
    ASSERT_HR(hr);

    hr = m_Device->CreatePixelShader(PixelShaderCode->GetBufferPointer(), PixelShaderCode->GetBufferSize(), nullptr, PixelShader.GetAddressOf());
    ASSERT_HR(hr);

    psInfo.code = std::move(PixelShaderCode);
    psInfo.shader = std::move(PixelShader);

    m_PixelShaders.insert(std::make_pair(filename, psInfo));
    return m_PixelShaders[filename];
}
