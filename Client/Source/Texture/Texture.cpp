#include "pch.h"
#include "Texture.h"

namespace CLIENT
{
	void CLIENT::Texture::Init(ID3D11Device* device, const wstring& path)
	{
		wstring filePath = L"../Source/IMG/" + path;
		
		ScratchImage image;

		ThrowIfFailed(LoadFromWICFile(filePath.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, image));

		ComPtr<ID3D11Texture2D> texture;

		ThrowIfFailed(CreateTexture(device, image.GetImages(), image.GetImageCount(), image.GetMetadata(), (ID3D11Resource**)texture.GetAddressOf()));

		D3D11_TEXTURE2D_DESC textureDesc;
		texture->GetDesc(&textureDesc);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		{
			ZeroMemory(&srvDesc, sizeof(srvDesc));

			srvDesc.ViewDimension             = D3D10_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels       = 1;
			srvDesc.Format                    = textureDesc.Format;

			ThrowIfFailed(device->CreateShaderResourceView(texture.Get(), &srvDesc, &mTexture));
		}
	}
}