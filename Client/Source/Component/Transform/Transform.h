#pragma once

#include "Component/Component.h"

namespace CLIENT
{
	class Transform final : public Component
	{
	public:
		enum class STATE
		{
			RIGHT,
			UP,
			LOOK,
			POSITION
		};
	private:
		matrix mWorldMatrix;
	public:
		virtual ~Transform() = default;
	protected:
		virtual HRESULT Init(const COMPONENT_INIT_DESC* desc) override;
	public:
		matrix GetWorldMatrix()
		{
			return mWorldMatrix;
		}
		matrix GetWorldMatrixInv()
		{
			return matrix::Inverse(mWorldMatrix);
		}
	public:
		vector3 GetState(STATE state);
		void    SetState(STATE state, vector3 v);
	public:
		static SharedPtr<Transform> Create(const COMPONENT_INIT_DESC* desc = nullptr);
	};
}