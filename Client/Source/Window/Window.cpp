#include "pch.h"
#include "Window.h"
#include "Input/Input.h"

namespace CLIENT
{
	vector<WindowCallBack> Window::mCallBack;

	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		/*for (auto& callBack : Window::mCallBack)
		{
			LRESULT result = callBack(hWnd, msg, wParam, lParam);
			if (result)
			{
				return result;
			}
		}

		switch (msg)
		{
		case WM_KEYDOWN:
		case WM_DESTROY:
			::PostQuitMessage(0);
			break;
		}*/
		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}

	void CLIENT::Window::Init()
	{
		WNDCLASSEXW wcex = {};
		{
			wcex.cbSize        = sizeof(WNDCLASSEX);
			wcex.style         = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc   = WndProc;
			wcex.cbClsExtra    = 0;
			wcex.cbWndExtra    = 0;
			wcex.hInstance     = ghInst = GetModuleHandle(NULL);
			wcex.hIcon         = LoadIcon(0, IDI_APPLICATION);
			wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
			wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName  = NULL;
			wcex.lpszClassName = L"Client";
			wcex.hIconSm       = LoadIcon(0, IDI_APPLICATION);

			RegisterClassExW(&wcex);
		}

		RECT rcWindow = { 0, 0, gScreenWidth, gScreenHeight };
		AdjustWindowRect(&rcWindow, WS_OVERLAPPEDWINDOW, false);

		ghWnd = CreateWindowW
		(
			L"Client",
			L"Client",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rcWindow.right - rcWindow.left,
			rcWindow.bottom - rcWindow.top,
			nullptr,
			nullptr,
			ghInst,
			nullptr
		);

		if (0 == ghWnd)
		{
			LOG_ERROR("Fail to Register Window");
		}

		ShowWindow(ghWnd, SW_NORMAL);
		UpdateWindow(ghWnd);

		LOG_INFO("Complete to Register Window");
	}

	bool CLIENT::Window::Update()
	{
		MSG msg;

		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message != WM_QUIT)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				return false;
			}

			if (GlobalInstance::Instance<Input>()->IsEscapePressed() == true)
			{
				return false;
			}
		}

		/*MSG msg;
		bool done;

		ZeroMemory(&msg, sizeof(MSG));

		done = false;

		while (!done)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (msg.message == WM_QUIT)
			{
				done = true;
			}
			else
			{
				if (GlobalInstance::Instance<Input>()->IsEscapePressed() == true)
				{
					done = true;
				}
			}
		}*/

		return true;
	}
}