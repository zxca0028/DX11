#pragma once

#include "Component/Component.h"

namespace CLIENT
{
	class Texture final : public Component
	{
	private:
		struct TargaHeader
		{
			byte data1[12];
			u16  width;
			u16  height;
			byte bpp;
			byte data2;
		};
	private:
		byte* mTargaData = nullptr;
	private:
		ID3D11ShaderResourceView* mTexture;
		ID3D11Texture2D* mTexture2D;
	public:
		virtual ~Texture() = default;
	protected:
		virtual HRESULT Init(const COMPONENT_INIT_DESC* desc) override;
	public:
		ID3D11ShaderResourceView* GetTexture() const
		{
			return mTexture;
		}
	public:
		static SharedPtr<Texture> Create(const COMPONENT_INIT_DESC* desc = nullptr);
	};
}