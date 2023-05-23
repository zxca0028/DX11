#include "pch.h"
#include "Input.h"

namespace CLIENT
{
	void Input::Init()
	{
		ThrowIfFailed(DirectInput8Create(ghInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mDirectInput, nullptr));

		ThrowIfFailed(mDirectInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, nullptr));
		ThrowIfFailed(mKeyboard->SetCooperativeLevel(ghWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));
		ThrowIfFailed(mKeyboard->SetDataFormat(&c_dfDIKeyboard));
		ThrowIfFailed(mKeyboard->Acquire());

		ThrowIfFailed(mDirectInput->CreateDevice(GUID_SysMouse, &mMouse, nullptr));
		ThrowIfFailed(mMouse->SetCooperativeLevel(ghWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));
		ThrowIfFailed(mMouse->SetDataFormat(&c_dfDIMouse));
		ThrowIfFailed(mMouse->Acquire());
	}

	void CLIENT::Input::Update()
	{
		ReadKeyboard();
		ReadMouse();
		ProcessInput();
	}

	bool CLIENT::Input::IsEscapePressed()
	{
		if (mKeyboardState[DIK_ESCAPE] & 0x80)
		{
			return true;
		}

		return false;
	}

	void CLIENT::Input::GetMouseLocation(i32& x, i32& y)
	{
		
	}

	bool Input::KeyInput(int keyCode)
	{
		if (mKeyboardState[keyCode] & 0x80)
		{
			return true;
		}

		return false;
	}

	void Input::MouseInput(i32& dx, i32& dy)
	{
		dx = mMouseState.lX;
		dy = mMouseState.lY;
	}

	void CLIENT::Input::ReadKeyboard()
	{
		HRESULT result = mKeyboard->GetDeviceState(sizeof(mKeyboardState), (LPVOID)&mKeyboardState);

		if (FAILED(result))
		{
			if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				mKeyboard->Acquire();
			}
		}
	}

	void CLIENT::Input::ReadMouse()
	{
		HRESULT result = mMouse->GetDeviceState(sizeof(mMouseState), (LPVOID)&mMouseState);

		if (FAILED(result))
		{
			if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				mMouse->Acquire();
			}
		}
	}

	void CLIENT::Input::ProcessInput()
	{
		mMouseX += mMouseState.lX;
		mMouseY += mMouseState.lY;

		if (mMouseX < 0) { mMouseX = 0; }
		if (mMouseY < 0) { mMouseY = 0; }

		if (mMouseX > mScreenWidth)  { mMouseX = mScreenWidth; }
		if (mMouseY > mScreenHeight) { mMouseY = mScreenHeight; }
	}
}
