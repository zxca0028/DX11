#pragma once

#include "D3D.h"

namespace CLIENT
{
	class Graphics
	{
	public:
		void Init();
		void Frame();
		void Render();
		void Destroy();
	private:
		UniquePtr<D3D> mD3D;
	};
}