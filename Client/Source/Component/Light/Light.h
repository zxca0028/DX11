#pragma once

#include "Component/Component.h"

namespace CLIENT
{
	class Light final : public Component
	{
	private:
		vector4 mDiffuseColor;
		vector3 mDirection;
	public:
		virtual ~Light() = default;
	public:
		virtual HRESULT Init(const COMPONENT_INIT_DESC* desc) override;
	public:
		void SetDiffuseColor(float r, float g, float b, float a);
		void SetDirection(float x, float y, float z);
	public:
		vector4 GetDiffuseColor() const
		{
			return mDiffuseColor;
		}
		vector3 GetDirection() const
		{
			return mDirection;
		}
	public:
		static SharedPtr<Light> Create(const COMPONENT_INIT_DESC* desc = nullptr);
	};
}