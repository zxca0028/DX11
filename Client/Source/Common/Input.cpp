#include "pch.h"
#include "Input.h"

namespace CLIENT
{
	void CLIENT::Input::Init()
	{
		mKeys.resize(256);
	}

	void CLIENT::Input::KeyUp(u32 key)
	{
		mKeys[key] = false;
	}

	void CLIENT::Input::KeyDown(u32 key)
	{
		mKeys[key] = true;
	}

	bool CLIENT::Input::IsKeyDown(u32 key)
	{
		return mKeys[key];
	}
}