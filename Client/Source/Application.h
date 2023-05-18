#pragma once

#include "Renderer/Renderer.h"
#include "Input/Input.h"

namespace CLIENT
{
	class Application
	{
	private:
		UniquePtr<class Renderer> mGraphics;
	public:
		bool Create();
		void Run();
		void Destroy();
	};
}