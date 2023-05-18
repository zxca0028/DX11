#include "pch.h"
#include "Application.h"
#include "DirectX11/D3D.h"
#include "Renderer/Renderer.h"
#include "Input/Input.h"
#include "Window/Window.h"
#include "GameObject/GameObjectMgr.h"
#include "DirectX11/Camera.h"

namespace CLIENT
{
    HINSTANCE ghInst;
    HWND      ghWnd;
    i32       gScreenWidth  = 1280;
    i32       gScreenHeight = 720;

    bool CLIENT::Application::Create()
    {
        GlobalInstance::Init();
        {
            GlobalInstance::Register<Log>();
            GlobalInstance::Register<Window>();
            GlobalInstance::Register<D3D>();
            GlobalInstance::Register<Renderer>();
            GlobalInstance::Register<Input>();

            GlobalInstance::Register<Camera>();
            GlobalInstance::Register<GameObjectMgr>();
        }

        return true;
    }

    void CLIENT::Application::Run()
    {
        while (true)
        {
			if (false == GlobalInstance::Instance<Window>()->Update())
			{
				break;
			}

            GlobalInstance::Instance<Input>()->Update();

			GlobalInstance::Instance<Camera>()->Render();
			GlobalInstance::Instance<GameObjectMgr>()->Update();

			GlobalInstance::Instance<D3D>()->BeginScene();

			GlobalInstance::Instance<GameObjectMgr>()->Render();

			GlobalInstance::Instance<D3D>()->EndScene();
        }
    }

    void CLIENT::Application::Destroy()
    {
        GlobalInstance::Release();
    }
}