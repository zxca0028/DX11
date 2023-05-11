#pragma once

#include "Core.h"

namespace CLIENT
{
	class Texture final
	{
	private:
		ID3D11ShaderResourceView* mTexture;
	public:
		void Init(ID3D11Device* device, const wstring& path);
	public:
		ID3D11ShaderResourceView* GetTexture() const
		{
			return mTexture;
		}
	};
}