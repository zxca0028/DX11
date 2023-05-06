#include "pch.h"
#include "Graphics.h"
#include "Window/Window.h"
#include "DirectX11/D3D.h"
#include "DirectX11/Camera.h"
#include "DirectX11/Model.h"
#include "Shaders/ColorShader.h"

namespace CLIENT
{
	void CLIENT::Graphics::Init()
	{
		mD3D = CreateSharedPtr<D3D>();
		mD3D->Init();

		mCamera = CreateSharedPtr<Camera>();
		mCamera->SetPosition(0.0f, 0.0f, -10.0f);

		mModel = CreateSharedPtr<Model>();
		mModel->Init(mD3D->GetDevice());

		mColorShader = CreateSharedPtr<ColorShader>();
		mColorShader->Init(mD3D->GetDevice(), GlobalInstance::Instance<Window>()->GetWindowDesc().hWnd);
	}

	void CLIENT::Graphics::Frame()
	{
		mD3D->Render();
	}

	void CLIENT::Graphics::Render()
	{
		mD3D->BeginScene();

		mCamera->Render();

		matrix worldMatrix;
		matrix viewMatrix;
		matrix projMatrix;

		mD3D->GetWorldMatrix(worldMatrix);
		mCamera->GetViewMatrix(viewMatrix);
		mD3D->GetProjMatrix(projMatrix);

		mModel->Render(mD3D->GetDeviceContext());

		mColorShader->Render(mD3D->GetDeviceContext(), mModel->GetIndexCount(), worldMatrix, viewMatrix, projMatrix);

		mD3D->EndScene();
	}

	void CLIENT::Graphics::Destroy()
	{
		mD3D->Destroy();
	}
}