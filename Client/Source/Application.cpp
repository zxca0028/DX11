#include "pch.h"
#include "Application.h"
#include "DirectX11/D3D.h"
#include "Global/Pipeline.h"
#include "Renderer/Renderer.h"
#include "Input/Input.h"
#include "Window/Window.h"
#include "GameObject/GameObjectMgr.h"

namespace CLIENT
{
    HINSTANCE ghInst;
    HWND      ghWnd;
    u32       gScreenWidth  = 1280;
    u32       gScreenHeight = 720;
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

            GlobalInstance::Register<GameObjectMgr>();
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.Fonts->AddFontFromFileTTF("../Font/Consolas.ttf", 16.0f);
        ImGui::StyleColorsDark();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplWin32_Init(ghWnd);
        ImGui_ImplDX11_Init(GlobalInstance::Instance<D3D>()->GetDevice(), GlobalInstance::Instance<D3D>()->GetDeviceContext());

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

            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();



            ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            const ImGuiViewport* viewport = ImGui::GetMainViewport();

            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);

            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            window_flags |= ImGuiWindowFlags_NoBackground;

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

			ImGui::Begin("DockingSpace", nullptr, window_flags);
			ImGui::PopStyleVar();
			ImGui::PopStyleVar(2);

			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("DockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			ImGui::End();

			GlobalInstance::Instance<D3D>()->BeginScene();


            ImGui::Begin("Hello, World!");
            ImGui::Text("This is some useful text.");
            ImGui::End();




			GlobalInstance::Instance<GameObjectMgr>()->Render();

            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();


			GlobalInstance::Instance<D3D>()->EndScene();
        }
    }

    void CLIENT::Application::Destroy()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        GlobalInstance::Release();
    }
}