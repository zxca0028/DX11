#include "pch.h"
#include "Application.h"
#include "DirectX11/D3D.h"
#include "Global/Pipeline.h"
#include "Renderer/Renderer.h"
#include "Input/Input.h"
#include "Window/Window.h"
#include "GameObject/GameObjectMgr.h"
#include "ClientUI/ClientUI.h"



namespace CLIENT
{
    HINSTANCE ghInst;
    HWND      ghWnd;
    u32       gScreenWidth  = 1920;
    u32       gScreenHeight = 1080;
    u32       gResizeWidth  = 0;
    u32       gResizeHeight = 0;

    bool CLIENT::Application::Create()
    {
        GlobalInstance::Init();
        {
            GlobalInstance::Register<Log>();
            GlobalInstance::Register<Window>();
            GlobalInstance::Register<D3D>();
            GlobalInstance::Register<Renderer>();
            GlobalInstance::Register<Pipeline>();
            GlobalInstance::Register<Input>();
            GlobalInstance::Register<ClientUI>();

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
			GlobalInstance::Instance<GameObjectMgr>()->Update();


            GlobalInstance::Instance<ClientUI>()->NewFrame();
			GlobalInstance::Instance<D3D>()->BeginScene();

            GlobalInstance::Instance<GameObjectMgr>()->Render();

            /*ImGui::Begin("Hello, World!");
            ImGui::Text("This is some useful text.");
            ImGui::End();*/

            GlobalInstance::Instance<ClientUI>()->EndFrame();
			GlobalInstance::Instance<D3D>()->EndScene();
        }
    }

    void CLIENT::Application::Destroy()
    {
        GlobalInstance::Instance<ClientUI>()->Shutdown();
        GlobalInstance::Release();
    }
}