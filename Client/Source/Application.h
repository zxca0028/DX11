#pragma once

#include "Renderer/Renderer.h"
#include "Common/Input.h"

namespace CLIENT
{
	class Application
	{
	private:
		UniquePtr<class Renderer> mGraphics;
		UniquePtr<class Input> mInput;
	public:
		bool Create();
		void Run();
		void Destroy();
	};
}