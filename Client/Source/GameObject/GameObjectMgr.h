#pragma once

#include "Core.h"

namespace CLIENT
{
	class GameObjectMgr final : public ISingleton
	{
	private:
		Dictionary<string, SharedPtr<class GameObject>> mObjectPool;
	public:
		virtual void Init() override;
	public:
		void Update();
		void Render();
	public:
		HRESULT AddGameObject(const string& objectName, SharedPtr<class GameObject> gameObject);
	};
}