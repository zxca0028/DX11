#pragma once

#include "Core.h"

namespace CLIENT
{
	class Model
	{
	private:
		struct VertexType
		{
			vector3 position;
			vector4 color;
		};
		struct VertexTexType
		{
			vector3 position;
			vector2 texture;
		};
	private:
		ID3D11Buffer* mVertexBuffer;
		ID3D11Buffer* mIndexBuffer;
		i32 mVertexCount;
		i32 mIndexCount;
	private:
		SharedPtr<class Texture> mTexture;
	public:
		void Init(ID3D11Device* device);
		void Render(ID3D11DeviceContext* context);
	private:
		void InitBuffers(ID3D11Device* device);
		void InitTexture(ID3D11Device* device, const wstring& fileName);
		void RenderBuffers(ID3D11DeviceContext* context);
	public:
		i32 GetIndexCount() const
		{
			return mIndexCount;
		}
		ID3D11ShaderResourceView* GetTexture() const;
	};
}