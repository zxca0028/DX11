#include "pch.h"
#include "Texture.h"
#include "DirectX11/D3D.h"

namespace CLIENT
{
	HRESULT CLIENT::Texture::Init(const COMPONENT_INIT_DESC* desc)
	{
		mInitDesc = *desc;

		wstring filePath = L"../Resource/Image/" + mInitDesc.path;
		
		ScratchImage image;
		
		//ThrowIfFailed(LoadFromWICFile(filePath.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, image));
		ThrowIfFailed(LoadFromDDSFile(filePath.c_str(), DDS_FLAGS_NONE, nullptr, image));

		ComPtr<ID3D11Texture2D> texture;

		ThrowIfFailed(CreateTexture(GlobalInstance::Instance<D3D>()->GetDevice(), image.GetImages(), image.GetImageCount(), image.GetMetadata(), (ID3D11Resource**)texture.GetAddressOf()));
		
		D3D11_TEXTURE2D_DESC textureDesc;
		texture->GetDesc(&textureDesc);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		{
			ZeroMemory(&srvDesc, sizeof(srvDesc));

			srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels       = 1;
			srvDesc.Format                    = textureDesc.Format;

			ThrowIfFailed(GlobalInstance::Instance<D3D>()->GetDevice()->CreateShaderResourceView(texture.Get(), &srvDesc, &mTexture));
		}

		//ThrowIfFailed(CreateShaderResourceView(GlobalInstance::Instance<D3D>()->GetDevice(), image.GetImages(), image.GetImageCount(), image.GetMetadata(), &mTexture));

		return S_OK;
	}

	SharedPtr<Texture> Texture::Create(const COMPONENT_INIT_DESC* desc)
	{
		auto component = CreateSharedPtr<Texture>();

		ThrowIfFailed(component->Init(desc));

		return component;
	}
}