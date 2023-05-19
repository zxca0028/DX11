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
		virtual HRESULT Init(const COMPONENT_INIT_DESC* desc) = 0;
		virtual void    Render() = 0;
	protected:
		virtual HRESULT InitBuffer() = 0;
		virtual void    RenderBuffer() = 0;
	public:
		i32 GetIndexCount() const
		{
			return mIndexCount;
		}
	};
}
