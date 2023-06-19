#include "pch.h"
#include "GameObject.h"
#include "GameObjectMgr.h"
#include "GameObject/TestObject/TestObj.h"
#include "GameObject/Camera/Camera.h"

namespace CLIENT
{
	void CLIENT::GameObjectMgr::Init()
	{
		GameObject::OBJECT_INIT_DESC cameraInitDesc;
		{
			cameraInitDesc.position = vector3(0.0f, 0.0f, -10.0f);

			ThrowIfFailed(AddGameObject("Camera", Camera::Create(&cameraInitDesc)));
		}

		GameObject::OBJECT_INIT_DESC obj_1_InitDesc;
		{
			//obj_1_InitDesc.texture = L"stone01.tga";
			obj_1_InitDesc.texture = L"Test.dds";
			//obj_1_InitDesc.texture  = L"grass.jpeg";
			//obj_1_InitDesc.shader = L"Color.hlsl";
			obj_1_InitDesc.shader   = L"Light.hlsl";
			obj_1_InitDesc.position = vector3(0.0f, 0.0f, 0.0f);

			ThrowIfFailed(AddGameObject("TestObj1", TestObj::Create(&obj_1_InitDesc)));
		}
		//GameObject::OBJECT_INIT_DESC obj_2_InitDesc;
		//{
		//	obj_2_InitDesc.texture  = L"stone.jpg";
		//	obj_2_InitDesc.shader   = L"Light.hlsl";
		//	obj_2_InitDesc.position = vector3(0.0f, 0.0f, 0.0f);

		//	ThrowIfFailed(AddGameObject("TestObj2", TestObj::Create(&obj_2_InitDesc)));
		//}
		//GameObject::OBJECT_INIT_DESC obj_3_InitDesc;
		//{
		//	obj_3_InitDesc.texture  = L"grass.jpeg";
		//	obj_3_InitDesc.shader   = L"Light.hlsl";
		//	obj_3_InitDesc.position = vector3(1.0f, 0.0f, 0.0f);

		//	ThrowIfFailed(AddGameObject("TestObj3", TestObj::Create(&obj_3_InitDesc)));
		//}
	}

	void GameObjectMgr::Update()
	{
		for (auto& object : mObjectPool)
		{
			object.second->Update();
		}
	}

	void GameObjectMgr::Render()
	{
		for (auto& object : mObjectPool)
		{
			object.second->Render();
		}
	}

	HRESULT GameObjectMgr::AddGameObject(const string& objectName, SharedPtr<class GameObject> gameObject)
	{
		if (mObjectPool.find(objectName) == mObjectPool.end())
		{
			mObjectPool.emplace(objectName, gameObject);

			return S_OK;
		}
		else
		{
			return E_FAIL;
		}
	}
}