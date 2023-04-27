#pragma once

#include "Core.h"

namespace CLIENT
{
	struct WindowDesc
	{
		HWND           hWnd   = nullptr;
		HINSTANCE      hInst  = nullptr;
		u32		       Width  = 0;
		u32		       Height = 0;
		const wchar_t* Title  = nullptr;
	};

	using WindowCallBack = std::function<LRESULT(HWND, UINT, WPARAM wParam, LPARAM lParam)>;

	class Window final : public ISingleton
	{
		friend class GlobalInstance;
		friend class Application;
	public:
		static WindowDesc mWindowDesc;
		static vector<WindowCallBack> mCallBack;
	public:
		virtual ~Window() = default;
	private:
		virtual void Init() override;
	private:
		bool Update();
	private:
		void SetWindowDesc();
	public:
		WindowDesc GetWindowDesc() const
		{
			return mWindowDesc;
		}
	};
}