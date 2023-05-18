#pragma once

#include "Core.h"

namespace CLIENT
{
	class Input final : public ISingleton
	{
	private:
		IDirectInput8*       mDirectInput = nullptr;
		IDirectInputDevice8* mKeyboard    = nullptr;
		IDirectInputDevice8* mMouse       = nullptr;
	private:
		DIMOUSESTATE mMouseState;
		byte mKeyboardState[256];
	private:
		i32 mScreenWidth;
		i32 mScreenHeight;
		i32 mMouseX;
		i32 mMouseY;
	public:
		virtual void Init() override;
	public:
		void Update();
		bool IsEscapePressed();
		void GetMouseLocation(i32& x, i32& y);
	private:
		void ReadKeyboard();
		void ReadMouse();
		void ProcessInput();
	};
}