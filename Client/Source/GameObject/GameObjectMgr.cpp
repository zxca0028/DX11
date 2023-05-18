#include "pch.h"
#include "GameObject.h"
#include "GameObjectMgr.h"
#include "GameObject/TestObject/TestObj.h"

namespace CLIENT
{
	void CLIENT::GameObjectMgr::Init()
	{
		GameObject::OBJECT_INIT_DESC objDesc_1;
		{
			objDesc_1.texture  = L"grass.jpeg";
			objDesc_1.position = vector3(-1.0f, 0.0f, 0.0f);

			ThrowIfFailed(AddGameObject("TestObj1", TestObj::Create(objDesc_1)));
		}
		GameObject::OBJECT_INIT_DESC objDesc_2;
		{
			objDesc_2.texture = L"stone.jpg";
			objDesc_2.position = vector3(0.0f, 0.0f, 0.0f);

			ThrowIfFailed(AddGameObject("TestObj2", TestObj::Create(objDesc_2)));
		}
		GameObject::OBJECT_INIT_DESC objDesc_3;
		{
			objDesc_3.texture = L"grass.jpeg";
			objDesc_3.position = vector3(1.0f, 0.0f, 0.0f);

			ThrowIfFailed(AddGameObject("TestObj3", TestObj::Create(objDesc_3)));
		}
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