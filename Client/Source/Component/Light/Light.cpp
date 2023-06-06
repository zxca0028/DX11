#include "pch.h"
#include "Light.h"

namespace CLIENT
{
	HRESULT CLIENT::Light::Init(const COMPONENT_INIT_DESC* desc)
	{
		if (nullptr != desc)
		{
			mInitDesc = *desc;
		}

		return S_OK;
	}

	void CLIENT::Light::SetDiffuseColor(float r, float g, float b, float a)
	{
		mDiffuseColor = vector4(r, g, b, a);
	}

	void CLIENT::Light::SetDirection(float x, float y, float z)
	{
		mDirection = vector3(x, y, z);
	}
	SharedPtr<Light> Light::Create(const COMPONENT_INIT_DESC* desc)
	{
		auto component = CreateSharedPtr<Light>();

		ThrowIfFailed(component->Init(desc));

		return component;
	}
}