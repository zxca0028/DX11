#pragma once

#include "Core.h"

namespace CLIENT
{
	class Model
	{
	private:
		struct VertexType
		{
			XMFLOAT3 position;
			XMFLOAT4 color;
		};
	private:
		ID3D11Buffer* mVertexBuffer;
		ID3D11Buffer* mIndexBuffer;
		i32 mVertexCount;
		i32 mIndexCount;
	public:
		void Init(ID3D11Device* device);
		void Render(ID3D11DeviceContext* context);
	private:
		void InitBuffers(ID3D11Device* device);
		void RenderBuffers(ID3D11DeviceContext* context);
	public:
		i32 GetIndexCount() const
		{
			return mIndexCount;
		}
	};
}