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

		ThrowIfFailed(LoadFromWICFile(filePath.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, image));

		ComPtr<ID3D11Texture2D> texture;

		ThrowIfFailed(CreateTexture(GlobalInstance::Instance<D3D>()->GetDevice(), image.GetImages(), image.GetImageCount(), image.GetMetadata(), (ID3D11Resource**)texture.GetAddressOf()));
		
		D3D11_TEXTURE2D_DESC textureDesc;
		texture->GetDesc(&textureDesc);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		{
			ZeroMemory(&srvDesc, sizeof(srvDesc));

			srvDesc.ViewDimension             = D3D10_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels       = 1;
			srvDesc.Format                    = textureDesc.Format;

			ThrowIfFailed(GlobalInstance::Instance<D3D>()->GetDevice()->CreateShaderResourceView(texture.Get(), &srvDesc, &mTexture));
		}

		/*byte* fileName = "../Resource/Image/skybox.dds";

		FILE* filePtr;
		fopen_s(&filePtr, fileName, "rb");
		
		TargaHeader targaFileHeader;
		u32 count = (u32)fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);

		i32 width  = (i32)targaFileHeader.width;
		i32 height = (i32)targaFileHeader.height;
		i32 bpp    = (i32)targaFileHeader.bpp;

		i32 imageSize = width * height * 4;

		byte* targaImage = new byte[imageSize];
		
		count = (u32)fread(targaImage, 1, imageSize, filePtr);

		fclose(filePtr);

		mTargaData = new byte[imageSize];

		i32 index = 0;
		i32 k = (width * height * 4) - (width * 4);

		for (i32 j = 0; j < height; ++j)
		{
			for (i32 i = 0; i < width; ++i)
			{
				mTargaData[index + 0] = targaImage[k + 2];
				mTargaData[index + 1] = targaImage[k + 1];
				mTargaData[index + 2] = targaImage[k + 0];
				mTargaData[index + 3] = targaImage[k + 3];

				k += 4;
				index += 4;
			}

			k -= (width * 8);
		}

		delete[] targaImage;
		targaImage = 0;

		D3D11_TEXTURE2D_DESC textureDesc;
		{
			textureDesc.Height = height;
			textureDesc.Width = width;
			textureDesc.MipLevels = 0;
			textureDesc.ArraySize = 1;
			textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.SampleDesc.Quality = 0;
			textureDesc.Usage = D3D11_USAGE_DEFAULT;
			textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
			textureDesc.CPUAccessFlags = 0;
			textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS | D3D11_RESOURCE_MISC_TEXTURECUBE;
		}

		ThrowIfFailed(GlobalInstance::Instance<D3D>()->GetDevice()->CreateTexture2D(&textureDesc, nullptr, &mTexture2D));

		u32 rowPitch = (width * 4) * sizeof(byte);

		GlobalInstance::Instance<D3D>()->GetDeviceContext()->UpdateSubresource(mTexture2D, 0, nullptr, mTargaData, rowPitch, 0);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		{
			srvDesc.Format = textureDesc.Format;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels = -1;
		}

		ThrowIfFailed(GlobalInstance::Instance<D3D>()->GetDevice()->CreateShaderResourceView(mTexture2D, &srvDesc, &mTexture));

		GlobalInstance::Instance<D3D>()->GetDeviceContext()->GenerateMips(mTexture);

		delete[] mTargaData;
		mTargaData = 0;*/

		return S_OK;
	}

	SharedPtr<Texture> Texture::Create(const COMPONENT_INIT_DESC* desc)
	{
		auto component = CreateSharedPtr<Texture>();

		ThrowIfFailed(component->Init(desc));

		return component;
	}
}