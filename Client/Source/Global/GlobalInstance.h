#pragma once

#include "Global/Define.h"

namespace CLIENT
{
	class ISingleton abstract
	{
	public:
		virtual ~ISingleton() = default;
	protected:
		virtual void Init() = 0;
	};

	class GlobalInstance final
	{
	private:
		static UniquePtr<GlobalInstance> mInstance;
	private:
		stack<u64> mRegistOrder;
		Dictionary<u64, SharedPtr<ISingleton>> mInstances;
	public:
		static void Init()
		{
			if (nullptr == mInstance)
			{
				mInstance = CreateUniquePtr<GlobalInstance>();
			}
		}
		static void Release()
		{
			mInstance->ReleaseInstance();
		}
		template<class T, class ...Args>
		static void Register(Args... args)
		{
			u64 hash = typeid(T).hash_code();

			if (nullptr == GlobalInstance::Instance()->FindInstance(hash))
			{
				auto instance = CreateSharedPtr<T>(args...);

				GlobalInstance::Instance()->RegisterInstance(hash, instance);

				instance->Init();
			}
		}
		template<class T>
		static SharedPtr<T> Instance()
		{
			return std::static_pointer_cast<T>(mInstance->FindInstance(typeid(T).hash_code()));
		}
		template<class T>
		static bool IsValid()
		{
			return mInstance->FindInstance(typeid(T).hash_code()) != nullptr;
		}
	private:
		static GlobalInstance* Instance()
		{
			return mInstance.get();
		}
		SharedPtr<ISingleton> FindInstance(u64 hash)
		{
			auto instance = mInstances.find(hash);

			if (instance == mInstances.end())
			{
				return nullptr;
			}

			return instance->second;
		}
		void RegisterInstance(u64 hash, SharedPtr<ISingleton> instance)
		{
			mInstances.emplace(hash, instance);
			mRegistOrder.push(hash);
		}
		void ReleaseInstance()
		{
			while (mRegistOrder.empty() == false)
			{
				auto order = mRegistOrder.top(); mRegistOrder.pop();

				auto instance = FindInstance(order);

				instance.reset();
			}

			mInstances.clear();
			mInstance.reset();
		}
	};
}