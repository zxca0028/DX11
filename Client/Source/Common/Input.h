#pragma once

#include "Core.h"

namespace CLIENT
{
	class Input final
	{
	public:
		void Init();
	public:
		void KeyUp(u32 key);
		void KeyDown(u32 key);
	public:
		bool IsKeyDown(u32 key);
	private:
		vector<bool> mKeys;
	};
}