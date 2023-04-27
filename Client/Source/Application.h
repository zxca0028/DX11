#pragma once

#include "DirectX11/Graphics.h"
#include "Common/Input.h"

namespace CLIENT
{
	class Application
	{
	private:
		UniquePtr<class Graphics> mGraphics;
		UniquePtr<class Input> mInput;
	public:
		bool Create();
		void Run();
		void Destroy();
	};
}