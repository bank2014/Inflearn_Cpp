#pragma once

struct VertexShaderInfo {
    ComPtr<ID3D11VertexShader> shader;
    ComPtr<ID3DBlob> code;
};

struct PixelShaderInfo {
    ComPtr<ID3D11PixelShader> shader;
    ComPtr<ID3DBlob> code;
};

class ShaderManager
{
public:
    static ShaderManager& GetInstance() {
        static ShaderManager instance;
        return instance;
    }
    void SetDevice(ComPtr<ID3D11Device>& device) { m_Device = device; }
    VertexShaderInfo GetVertexShader(const std::wstring& filename);
    PixelShaderInfo GetPixelShader(const std::wstring& filename);

private:
    ShaderManager() {}
    ~ShaderManager() {
        m_VertexShaders.clear();
        m_PixelShaders.clear();
    }

    std::unordered_map<std::wstring, VertexShaderInfo> m_VertexShaders;
    std::unordered_map<std::wstring, PixelShaderInfo> m_PixelShaders;
    ComPtr<ID3D11Device> m_Device;
};

#define SHADER_MANAGER ShaderManager::GetInstance()
inline ShaderManager& GetShaderManager() { return ShaderManager::GetInstance(); }
