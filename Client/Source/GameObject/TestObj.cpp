#include "pch.h"
#include "TestObj.h"
#include "Window/Window.h"
#include "DirectX11/D3D.h"
#include "DirectX11/Camera.h"
#include "Geometry/Rect.h"
#include "Texture/Texture.h"
#include "Shaders/TextureShader.h"

namespace CLIENT
{
	void CLIENT::TestObj::Init()
	{
		mRect = CreateSharedPtr<Rect>();
		mRect->Init(GlobalInstance::Instance<D3D>()->GetDevice());

		mTexture = CreateSharedPtr<Texture>();
		mTexture->Init(GlobalInstance::Instance<D3D>()->GetDevice(), L"grass.jpeg");

		mShader = CreateSharedPtr<TextureShader>();
		mShader->Init(GlobalInstance::Instance<D3D>()->GetDevice(), GlobalInstance::Instance<Window>()->GetWindowDesc().hWnd);
	}

	void CLIENT::TestObj::Update()
	{
	}

	void CLIENT::TestObj::Render()
	{
		auto context    = GlobalInstance::Instance<D3D>()->GetDeviceContext();
		auto indexCount = mRect->GetIndexCount();
		auto srv        = mTexture->GetTexture();

		matrix worldMatrix; GlobalInstance::Instance<D3D>()->GetWorldMatrix(worldMatrix);
		matrix projMatrix;  GlobalInstance::Instance<D3D>()->GetProjMatrix(projMatrix);
		matrix viewMatrix;  GlobalInstance::Instance<Camera>()->GetViewMatrix(viewMatrix);

		mRect->Render(context);
		mShader->Render(context, indexCount, worldMatrix, viewMatrix, projMatrix, srv);
		mTexture->GetTexture();
	}

	void CLIENT::TestObj::UpdateObject()
	{
	}

	void CLIENT::TestObj::RenderObject()
	{
	}
}