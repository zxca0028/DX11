#include "pch.h"
#include "TestObj.h"
#include "Window/Window.h"
#include "DirectX11/D3D.h"
#include "DirectX11/Camera.h"
#include "Component/Geometry/Rect.h"
#include "Component/Texture/Texture.h"
#include "Component/Shaders/TextureShader.h"

namespace CLIENT
{
	HRESULT CLIENT::TestObj::Init(const OBJECT_INIT_DESC& desc)
	{
		mInitDesc = desc;

		mRect = CreateSharedPtr<Rect>();
		mRect->Init(GlobalInstance::Instance<D3D>()->GetDevice());

		mTexture = CreateSharedPtr<Texture>();
		mTexture->Init(GlobalInstance::Instance<D3D>()->GetDevice(), mInitDesc.texture);

		mShader = CreateSharedPtr<TextureShader>();
		mShader->Init(GlobalInstance::Instance<D3D>()->GetDevice(), ghWnd);

		return S_OK;
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
		
		worldMatrix._41 = mInitDesc.position.x;
		worldMatrix._42 = mInitDesc.position.y;
		worldMatrix._43 = mInitDesc.position.z;

		matrix projMatrix;  GlobalInstance::Instance<D3D>()->GetProjMatrix(projMatrix);
		matrix viewMatrix;  GlobalInstance::Instance<Camera>()->GetViewMatrix(viewMatrix);

		mRect->Render(context);
		mShader->Render(context, indexCount, worldMatrix, viewMatrix, projMatrix, srv);
	}

	void CLIENT::TestObj::UpdateObject()
	{
	}

	void CLIENT::TestObj::RenderObject()
	{
	}

	SharedPtr<TestObj> TestObj::Create(const OBJECT_INIT_DESC& desc)
	{
		auto object = CreateSharedPtr<TestObj>();

		ThrowIfFailed(object->Init(desc));

		return object;
	}
}