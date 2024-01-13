#pragma once
#include "Global.h"
#include "AActor.h"

class Girl : public UPrimitiveComponent
{
public:
    Girl() {
        const std::wstring shaderFile = L"shader/BasicShader.hlsl";
        const std::wstring TextureFile = L"../_EXTERNAL/res/girl.jpg";
        XMFLOAT3 pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
        XMFLOAT3 scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
        XMFLOAT3 rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
        m_pRootComponent = make_unique<UPrimitiveComponent>(shaderFile, TextureFile, pos, scale, rotation);
        m_ID = 0;
        m_CurrentSceneID = 0; // 필수 지정
    }
    virtual ~Girl() = default;

    virtual void BeginPlay() {
        UPrimitiveComponent::BeginPlay();

    }
    virtual void Tick(float deltaTime) {
        UPrimitiveComponent::Tick(deltaTime);

    }
    virtual void EndPlay() {
        UPrimitiveComponent::EndPlay();

    }
};
