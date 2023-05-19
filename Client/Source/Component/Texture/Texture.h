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