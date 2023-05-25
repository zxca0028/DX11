#pragma once

#include "Core.h"

namespace CLIENT
{
	class Application
	{
	private:
		//UniquePtr<class Renderer> mGraphics;
	public:
		bool Create();
		void Run();
		void Destroy();
	};
}