#include "pch.h"
#include "Application.h"
#include "DirectX11/Graphics.h"

#include "Common/Input.h"

#include "Window/Window.h"


namespace CLIENT
{
    bool CLIENT::Application::Create()
    {
        GlobalInstance::Init();
        {
            GlobalInstance::Register<Log>();
            GlobalInstance::Register<Window>();
        }

        mInput    = CreateUniquePtr<Input>();
        mInput->Init();

        mGraphics = CreateUniquePtr<Graphics>();
        mGraphics->Init();

        return true;
    }

    void CLIENT::Application::Run()
    {
        while (true)
        {
            if (GlobalInstance::IsValid<Window>())
            {
                // ≈∏¿Ã∏”

                if (false == GlobalInstance::Instance<Window>()->Update())
                {
                    break;
                }

                mGraphics->Render();
            }
        }
    }

    void CLIENT::Application::Destroy()
    {
        GlobalInstance::Release();
    }
}