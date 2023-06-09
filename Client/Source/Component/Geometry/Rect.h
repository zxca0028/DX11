#pragma once

#include "Geometry.h"

namespace CLIENT
{
	class Rect final : public Geometry
	{
	public:
		virtual ~Rect() = default;
	public:
		virtual HRESULT Init(const COMPONENT_INIT_DESC* desc) override;
		virtual void    Render() override;
	private:
		virtual HRESULT InitBuffer() override;
		virtual void    RenderBuffer() override;
	public:
		static SharedPtr<Rect> Create(const COMPONENT_INIT_DESC* desc = nullptr);
	};
}



