#pragma once

#include "Geometry.h"

namespace CLIENT
{
	class Rect final : public Geometry
	{
	private:
		struct VertexTexType
		{
			vector3 position;
			vector2 texture;
		};
	public:
		virtual ~Rect() = default;
	public:
		virtual HRESULT Init(ID3D11Device* device) override;
		virtual void    Render(ID3D11DeviceContext* context) override;
	private:
		virtual HRESULT InitBuffer(ID3D11Device* device) override;
		virtual void    RenderBuffer(ID3D11DeviceContext* context) override;
	};
}



