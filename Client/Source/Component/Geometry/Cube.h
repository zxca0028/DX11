#pragma once

#include "Geometry.h"

namespace CLIENT
{
	class Cube final : public Geometry
	{
	private:
		struct ModelType
		{
			f32 x, y, z;
			f32 u, v;
			f32 nx, ny, nz;
		};
	private:
		ModelType* mModelType = nullptr;
	public:
		virtual ~Cube() = default;
	public:
		virtual HRESULT Init(const COMPONENT_INIT_DESC* desc) override;
		virtual void    Render() override;
	private:
		virtual HRESULT InitBuffer() override;
		virtual void    RenderBuffer() override;
	public:
		static SharedPtr<Cube> Create(const COMPONENT_INIT_DESC* desc = nullptr);
	};
}
