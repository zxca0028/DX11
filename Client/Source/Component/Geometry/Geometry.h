#pragma once

#include "Component/Component.h"

namespace CLIENT
{
	class Geometry abstract : public Component
	{
	protected:
		ID3D11Buffer* mVertexBuffer = nullptr;
		ID3D11Buffer* mIndexBuffer  = nullptr;
	protected:
		i32 mVertexCount = 0;
		i32 mIndexCount  = 0;
	protected:
		virtual ~Geometry() = default;
	public:
		virtual HRESULT Init(ID3D11Device* device) = 0;
		virtual void    Render(ID3D11DeviceContext* context) = 0;
	protected:
		virtual HRESULT InitBuffer(ID3D11Device* device) = 0;
		virtual void    RenderBuffer(ID3D11DeviceContext* context) = 0;
	public:
		i32 GetIndexCount() const
		{
			return mIndexCount;
		}
	};
}
