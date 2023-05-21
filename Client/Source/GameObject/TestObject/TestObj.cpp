#include "pch.h"
#include "TestObj.h"
#include "Window/Window.h"
#include "DirectX11/D3D.h"
#include "Global/Pipeline.h"
#include "GameObject/Camera/Camera.h"
#include "Component/Geometry/Rect.h"
#include "Component/Texture/Texture.h"
#include "Component/Shaders/TextureShader.h"

namespace CLIENT
{
	HRESULT CLIENT::TestObj::Init(const OBJECT_INIT_DESC* desc)
	{
		mInitDesc = *desc;

		mRect = Rect::Create();

		Component::COMPONENT_INIT_DESC textureInitDesc;
		{
			textureInitDesc.path = mInitDesc.texture;

			mTexture = Texture::Create(&textureInitDesc);
		}

		Component::COMPONENT_INIT_DESC shaderInitDesc;
		{
			shaderInitDesc.path = mInitDesc.shader;

			mShader = TextureShader::Create(&shaderInitDesc);
		}

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

		matrix projMatrix=  GlobalInstance::Instance<Pipeline>()->GetMatrix(Pipeline::STATE::PROJ);


		matrix viewMatrix=  GlobalInstance::Instance<Pipeline>()->GetMatrix(Pipeline::STATE::VIEW);

		mRect->Render();
		mShader->Render(context, indexCount, worldMatrix, viewMatrix, projMatrix, srv);
	}

	void CLIENT::TestObj::UpdateObject()
	{
	}

	void CLIENT::TestObj::RenderObject()
	{
	}

	SharedPtr<TestObj> TestObj::Create(const OBJECT_INIT_DESC* desc)
	{
		auto object = CreateSharedPtr<TestObj>();

		ThrowIfFailed(object->Init(desc));

		return object;
	}
}