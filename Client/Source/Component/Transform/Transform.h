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
		void SetWorldMatrix(const matrix& m)
		{
			mWorldMatrix = m;
		}
		matrix GetWorldMatrixInv()
		{
			return matrix::Inverse(mWorldMatrix);
		}
	public:
		vector3 GetState(STATE state);
		void    SetState(STATE state, vector3 v);
	public:
		void Move(f32 deltaTime);
		void Back(f32 deltaTime);
		void Left(f32 deltaTime);
		void Right(f32 deltaTime);
		void Up(f32 deltaTime);
		void Down(f32 deltaTime);
	public:
		void RotationAxis(vector3 axis, f32 delta);
	public:
		static SharedPtr<Transform> Create(const COMPONENT_INIT_DESC* desc = nullptr);
	};
}