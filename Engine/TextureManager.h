#pragma once
struct TextureInfo {
	ComPtr<ID3D11ShaderResourceView> textureView;
};

class TextureManager
{
public:
	static TextureManager& GetInstance() {
		static TextureManager instance;
		return instance;
	}
    void SetDevice(ComPtr<ID3D11Device>& device) { m_Device = device;}
	TextureInfo GetTexture(const std::wstring& filePath);

private:
	HRESULT LoadTextureFromFile(const std::wstring& filename, TextureInfo& textureInfo);
	TextureManager() {}
	~TextureManager() { m_Textures.clear(); }
	
	std::unordered_map<std::wstring, TextureInfo> m_Textures;
	ComPtr<ID3D11Device> m_Device;
};

#define TEXTURE_MANAGER TextureManager::GetInstance()
inline TextureManager& GetTextureManager() { return TextureManager::GetInstance(); }