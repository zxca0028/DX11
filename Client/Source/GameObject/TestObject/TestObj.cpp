#include "pch.h"
#include "TestObj.h"
#include "Window/Window.h"
#include "DirectX11/D3D.h"
#include "Global/Pipeline.h"
#include "GameObject/Camera/Camera.h"

#include "Input/Input.h"

#include "Component/Geometry/Rect.h"
#include "Component/Geometry/Cube.h"
#include "Component/Texture/Texture.h"
#include "Component/Shaders/TextureShader.h"
#include "Component/Shaders/LightShader.h"
#include "Component/Shaders/ColorShader.h"
#include "Component/Transform/Transform.h"

namespace CLIENT
{
	HRESULT CLIENT::TestObj::Init(const OBJECT_INIT_DESC* desc)
	{
		mInitDesc = *desc;

		//mRect = Rect::Create();
		mCube = Cube::Create();

		Component::COMPONENT_INIT_DESC textureInitDesc;
		{
			textureInitDesc.path = mInitDesc.texture;

			mTexture = Texture::Create(&textureInitDesc);
		}

		Component::COMPONENT_INIT_DESC shaderInitDesc;
		{
			shaderInitDesc.path = mInitDesc.shader;

			//mShader = ColorShader::Create(&shaderInitDesc);
			mShader = LightShader::Create(&shaderInitDesc);
		}

		Component::COMPONENT_INIT_DESC transformInitDesc;
		{
			transformInitDesc.position = mInitDesc.position;
			mTransform = Transform::Create(&transformInitDesc);
		}

		return S_OK;
	}

	void CLIENT::TestObj::Update()
	{
		//if (GlobalInstance::Instance<Input>()->KeyInput(DIK_RIGHTARROW))
		//{
		//	mTransform->RotationAxis(vector3(0.f, 1.f, 0.f), 0.001f);
		//}

		mTransform->RotationAxis(vector3(1.f, 0.f, 0.f), 0.0001f);
		mTransform->RotationAxis(vector3(0.f, 1.f, 0.f), 0.0001f);
		//mTransform->RotationAxis(vector3(0.f, 0.f, 1.f), 0.0001f);

	}

	void CLIENT::TestObj::Render()
	{
		auto context    = GlobalInstance::Instance<D3D>()->GetDeviceContext();
		//auto indexCount = mRect->GetIndexCount();
		auto indexCount = mCube->GetIndexCount();
		auto srv        = mTexture->GetTexture();

		matrix worldMatrix = mTransform->GetWorldMatrix();
		matrix projMatrix  = GlobalInstance::Instance<Pipeline>()->GetMatrix(Pipeline::STATE::PROJ);
		matrix viewMatrix  = GlobalInstance::Instance<Pipeline>()->GetMatrix(Pipeline::STATE::VIEW);

		//mRect->Render();
		mCube->Render();
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