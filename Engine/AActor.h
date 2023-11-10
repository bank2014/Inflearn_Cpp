#pragma once
#include "Geometry.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "D3D11Renderer.h"

class UPrimitiveComponent
{
    struct ConstBufferDesc
    {
        XMMATRIX WorldMatrix;
        XMMATRIX ViewMatrix;
        XMMATRIX ProjMatrix;
    };
    struct Vertex
    {
        XMFLOAT4 Position;
        XMFLOAT2 UV;
    };
public:
    UPrimitiveComponent() = delete;
    UPrimitiveComponent(const std::wstring& shaderFile, const std::wstring& TextureFile, XMFLOAT3& pos, XMFLOAT3& scale, XMFLOAT3& rotation) {
        m_Position = pos;
        m_Scale = scale;
        m_Rotation = rotation;
        m_AABB = { pos.x, pos.y, scale.x, scale.y };

        LoadVertexShader(shaderFile);
        LoadPixelShader(shaderFile);
        LoadTexture(TextureFile);
        CreateConstantBuffer();

        CreateVertexData();
        CreateVertexBuffer();

        // 일단 야매로 만들어놓음
        const D3D11_INPUT_ELEMENT_DESC desc[] =
        {
            { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD0",  0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };
        CreateInputLayout(desc);

        UpdateWorldMatrix();
        SetPipelineState();
    }
    virtual ~UPrimitiveComponent() = default;

    void SetDevice(ComPtr<ID3D11Device>& device) { m_Device = device; }
    void SetDeviceContext(ComPtr<ID3D11DeviceContext>& context) { m_ImmediateContext = context; }

    virtual void BeginPlay() { }
    virtual void Tick(float deltaTime) { }
    virtual void Render() {
        UpdateWorldMatrix();
        SetPipelineState();
        Draw();
    }

protected:

    void CreateConstantBuffer() {
        D3D11_BUFFER_DESC Desc{};
        Desc.ByteWidth = sizeof(ConstBufferDesc);
        Desc.Usage = D3D11_USAGE_DEFAULT;
        Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

        HRESULT hr = m_Device->CreateBuffer(
            &Desc,
            nullptr,
            m_ConstBuffer.GetAddressOf());
        assert(SUCCEEDED(hr));
    }
    void CreateVertexData() {
        m_Vertices.resize(6);
        m_Vertices[0].UV.x = 0.0f; m_Vertices[0].UV.y = 0.0f;
        m_Vertices[1].UV.x = 1.0f; m_Vertices[1].UV.y = 0.0f;
        m_Vertices[2].UV.x = 0.0f; m_Vertices[2].UV.y = 1.0f;
        m_Vertices[3].UV.x = 0.0f; m_Vertices[3].UV.y = 1.0f;
        m_Vertices[4].UV.x = 1.0f; m_Vertices[4].UV.y = 0.0f;
        m_Vertices[5].UV.x = 1.0f; m_Vertices[5].UV.y = 1.0f;

        m_Vertices[0].Position.x = -1.0f; m_Vertices[0].Position.y = 1.0f;  m_Vertices[0].Position.z = 0.0f;
        m_Vertices[1].Position.x = 1.0f; m_Vertices[1].Position.y = 1.0f;  m_Vertices[1].Position.z = 0.0f;
        m_Vertices[2].Position.x = -1.0f; m_Vertices[2].Position.y = -1.0f;  m_Vertices[2].Position.z = 0.0f;
        m_Vertices[3] = m_Vertices[2];
        m_Vertices[4] = m_Vertices[1];
        m_Vertices[5].Position.x = 1.0f; m_Vertices[5].Position.y = -1.0f;  m_Vertices[5].Position.z = 0.0f;
    }
    void CreateVertexBuffer() {
        D3D11_BUFFER_DESC Desc{};
        Desc.ByteWidth = sizeof(Vertex) * m_Vertices.size();
        Desc.Usage = D3D11_USAGE_DEFAULT;
        Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA InitialData{};
        InitialData.pSysMem = &m_Vertices.at(0);

        HRESULT hr = m_Device->CreateBuffer(&Desc, &InitialData, m_VertexBuffer.GetAddressOf());
        assert(SUCCEEDED(hr));
    }
    void CreateIndexData() { }
    void CreateIndexBuffer() { }
    void LoadVertexShader(const std::wstring& filename) {
        m_VertexShaderInfo = SHADER_MANAGER.GetVertexShader(filename);
    }
    void LoadPixelShader(const std::wstring& filename) {
        m_PixelShaderInfo = SHADER_MANAGER.GetPixelShader(filename);
    }
    void LoadTexture(const std::wstring& filename) {
        m_TextureInfo = TEXTURE_MANAGER.GetTexture(filename);
    }
    void CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* vsInputDesc)
    {
        UINT count = sizeof(vsInputDesc) / sizeof(vsInputDesc[0]);

        if (m_VertexShaderInfo.code.Get() != nullptr)
        {
            HRESULT hr = m_Device->CreateInputLayout(
                vsInputDesc,
                count,
                m_VertexShaderInfo.code->GetBufferPointer(),
                m_VertexShaderInfo.code->GetBufferSize(),
                m_InputLayout.GetAddressOf());
            assert(SUCCEEDED(hr));
        }
    }
    void SetPipelineState() {
        m_ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        m_ImmediateContext->VSSetConstantBuffers(0, 1, m_ConstBuffer.GetAddressOf());
        m_ImmediateContext->PSSetShaderResources(0, 1, m_TextureInfo.textureView.GetAddressOf());
        m_ImmediateContext->VSSetShader(m_VertexShaderInfo.shader.Get(), nullptr, 0);
        m_ImmediateContext->IASetInputLayout(m_InputLayout.Get());
        m_ImmediateContext->PSSetShader(m_PixelShaderInfo.shader.Get(), nullptr, 0);
        const UINT stride = sizeof(Vertex);
        const UINT offset = 0;
        m_ImmediateContext->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);
    }

    void UpdateTransformationMatrices(const XMMATRIX* matWorld, const XMMATRIX* matView, const XMMATRIX* matProj) {
        if (matWorld != nullptr) m_WorldMatrix = *matWorld;
        if (matView != nullptr) m_ViewMatrix = *matView;
        if (matProj != nullptr) m_ProjMatrix = *matProj;

        // Transpose matrices for shader compatibility & Update constant buffer data
        m_ConstBufferData.WorldMatrix = XMMatrixTranspose(m_WorldMatrix);
        m_ConstBufferData.ViewMatrix = XMMatrixTranspose(m_ViewMatrix);
        m_ConstBufferData.ProjMatrix = XMMatrixTranspose(m_ProjMatrix);

        // Update the constant buffer resource
        m_ImmediateContext->UpdateSubresource(m_ConstBuffer.Get(), 0, nullptr, &m_ConstBufferData, 0, 0);
    }
    void UpdateWorldMatrix() {
        m_WorldMatrix = XMMatrixIdentity();

        XMVECTOR vScale = XMLoadFloat3(&m_Scale);
        XMVECTOR vRotation = XMLoadFloat3(&m_Rotation);
        XMVECTOR vPosition = XMLoadFloat3(&m_Position);

        XMMATRIX matScale = XMMatrixScalingFromVector(vScale);
        XMMATRIX matRotation = XMMatrixRotationRollPitchYawFromVector(vRotation);
        XMMATRIX matTranslate = XMMatrixTranslationFromVector(vPosition);

        m_WorldMatrix = matScale * matRotation * matTranslate;
    }
    void Draw() {
        m_ImmediateContext->Draw(m_Vertices.size(), 0);
    }

protected:
    XMFLOAT3    m_Position;
    XMFLOAT3    m_Scale;
    XMFLOAT3    m_Rotation;
    Util::Rect  m_AABB;

    ComPtr<ID3D11Device>        m_Device;
    ComPtr<ID3D11DeviceContext> m_ImmediateContext;
    ComPtr<ID3D11Buffer>        m_ConstBuffer;
    ConstBufferDesc             m_ConstBufferData;
    ComPtr<ID3D11Buffer>        m_VertexBuffer;
    std::vector<Vertex>         m_Vertices;
    ComPtr<ID3D11InputLayout>   m_InputLayout;

    VertexShaderInfo            m_VertexShaderInfo;
    PixelShaderInfo             m_PixelShaderInfo;
    TextureInfo                 m_TextureInfo;

    XMMATRIX                    m_WorldMatrix;
    XMMATRIX                    m_ViewMatrix;
    XMMATRIX                    m_ProjMatrix;
};

//class USpriteComponent : public UPrimitiveComponent
//{
//    struct SpriteDesc
//    {
//        // required
//        WSTR		TextureName;
//        WSTR		ShaderFileName;
//        XMFLOAT3	Position;
//        XMFLOAT3	scale;
//        int			RowCount;
//        int			ColumnCount;
//        float		TotalAnimTimeInSecond;
//        // optional
//        WSTR		    AlphaTextureFileName;
//        const Texture* AlphaTexture = nullptr;
//        std::vector<std::wstring> TextureFileNameList;
//        // dont touch
//        float		ElapsedTime = 0.f;
//        float		OffsetTime = 0.f;
//        int			CurrentAnimFrameIndex = 0;
//    };
//    struct UVFrame
//    {
//        TVector2 m_Min;
//        TVector2 m_Max;
//    };
//public:
//    virtual void TickComponent(float deltaTime) {}
//    USpriteComponent() = delete;
//protected:
//    SpriteDesc				Sprite;
//    std::vector<UVFrame>	UVFrameList;
//
//public:
//    void InitThis(SpriteDesc& desc);
//
//    bool Init();
//    bool TickComponent();
//    bool Render();
//    bool Release();
//};
