#pragma once

#include "Core.h"

namespace CLIENT
{
	using WindowCallBack = std::function<LRESULT(HWND, UINT, WPARAM wParam, LPARAM lParam)>;

	class Window final : public ISingleton
	{
		friend class GlobalInstance;
		friend class Application;
	public:
		static vector<WindowCallBack> mCallBack;
	public:
		virtual ~Window() = default;
	private:
		virtual void Init() override;
	private:
		bool Update();

	};
}