#pragma once

#include "Component/Component.h"

namespace CLIENT
{
	class Texture final : public Component
	{
	private:
		ID3D11ShaderResourceView* mTexture;
	public:
		virtual ~Texture() = default;
	public:
		void Init(ID3D11Device* device, const wstring& path);
	public:
		ID3D11ShaderResourceView* GetTexture() const
		{
			return mTexture;
		}
	};
}