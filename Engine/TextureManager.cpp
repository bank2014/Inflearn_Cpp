#include "pch.h"
#include "TextureManager.h"

TextureInfo TextureManager::GetTexture(const std::wstring& filename)
{
    auto iter = m_Textures.find(filename);
    if (m_Textures.end() != iter) {
        return iter->second;
    }
    
    TextureInfo textureInfo{};
    ASSERT_HR(LoadTextureFromFile(filename, textureInfo));
    return m_Textures[filename];
}

HRESULT TextureManager::LoadTextureFromFile(const std::wstring& filename, TextureInfo& textureInfo)
{
    HRESULT hr{};
    auto imageobj = std::make_unique<DirectX::ScratchImage>();
    DirectX::TexMetadata metadata{};

    hr = DirectX::GetMetadataFromDDSFile(filename.c_str(), DirectX::DDS_FLAGS_NONE, metadata);
    if (SUCCEEDED(hr)) {
        hr = DirectX::LoadFromDDSFile(filename.c_str(), DirectX::DDS_FLAGS_NONE, &metadata, *imageobj);
    }
    else {
        hr = DirectX::GetMetadataFromWICFile(filename.c_str(), DirectX::WIC_FLAGS_NONE, metadata);
        if (SUCCEEDED(hr)) {
            hr = DirectX::LoadFromWICFile(filename.c_str(), DirectX::WIC_FLAGS_NONE, &metadata, *imageobj);
        }
        else {
            hr = DirectX::GetMetadataFromTGAFile(filename.c_str(), DirectX::TGA_FLAGS_NONE, metadata);
            if (SUCCEEDED(hr)) {
                hr = DirectX::LoadFromTGAFile(filename.c_str(), DirectX::TGA_FLAGS_NONE, &metadata, *imageobj);
            }
        }
    }

    if (SUCCEEDED(hr)) {
        hr = DirectX::CreateShaderResourceView(m_Device.Get(), imageobj->GetImages(),imageobj->GetImageCount(), metadata,textureInfo.textureView.GetAddressOf());

        m_Textures.insert(std::make_pair(filename, textureInfo));
    }

    return hr;
}