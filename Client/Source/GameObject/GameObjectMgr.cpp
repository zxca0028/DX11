#include "pch.h"
#include "GameObject.h"
#include "GameObjectMgr.h"
#include "GameObject/TestObj.h"

namespace CLIENT
{
	void CLIENT::GameObjectMgr::Init()
	{
		AddGameObject("TestObj", CreateSharedPtr<TestObj>());
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

	void GameObjectMgr::AddGameObject(const string& objectName, SharedPtr<class GameObject> gameObject)
	{
		if (mObjectPool.find(objectName) == mObjectPool.end())
		{
			mObjectPool.emplace(objectName, gameObject);

			gameObject->Init();
		}
	}
}