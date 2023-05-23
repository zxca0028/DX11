#include "pch.h"
#include "Transform.h"

namespace CLIENT
{
	HRESULT Transform::Init(const COMPONENT_INIT_DESC* desc)
	{
		mInitDesc = *desc;

		SetState(STATE::POSITION, mInitDesc.position);

		return S_OK;
	}

	vector3 Transform::GetState(STATE state)
	{
		return *(vector3*)(&mWorldMatrix[(i32)state]);
	}

	void Transform::SetState(STATE state, vector3 v)
	{
		memcpy(&mWorldMatrix[(i32)state], &v, sizeof(vector3));
	}

	void Transform::Move(f32 deltaTime)
	{
		vector3 vPos  = GetState(STATE::POSITION);
		vector3 vLook = vector3::Normalize(GetState(STATE::LOOK));

		vPos += vLook * deltaTime;

		SetState(STATE::POSITION, vPos);
	}

	void Transform::Back(f32 deltaTime)
	{
		vector3 vPos  = GetState(STATE::POSITION);
		vector3 vLook = vector3::Normalize(GetState(STATE::LOOK));

		vPos -= vLook * deltaTime;

		SetState(STATE::POSITION, vPos);
	}

	void Transform::Left(f32 deltaTime)
	{
		vector3 vPos  = GetState(STATE::POSITION);
		vector3 vLook = vector3::Normalize(GetState(STATE::RIGHT));

		vPos -= vLook * deltaTime;

		SetState(STATE::POSITION, vPos);
	}

	void Transform::Right(f32 deltaTime)
	{
		vector3 vPos  = GetState(STATE::POSITION);
		vector3 vLook = vector3::Normalize(GetState(STATE::RIGHT));

		vPos += vLook * deltaTime;

		SetState(STATE::POSITION, vPos);
	}

	void Transform::Up(f32 deltaTime)
	{
		vector3 vPos  = GetState(STATE::POSITION);
		vector3 vLook = vector3::Normalize(GetState(STATE::UP));

		vPos += vLook * deltaTime;

		SetState(STATE::POSITION, vPos);
	}

	void Transform::Down(f32 deltaTime)
	{
		vector3 vPos  = GetState(STATE::POSITION);
		vector3 vLook = vector3::Normalize(GetState(STATE::UP));

		vPos -= vLook * deltaTime;

		SetState(STATE::POSITION, vPos);
	}

	void Transform::RotationAxis(vector3 axis, f32 delta)
	{
		vector3 vRight = GetState(STATE::RIGHT);
		vector3 vUp    = GetState(STATE::UP);
		vector3 vLook  = GetState(STATE::LOOK);

		matrix rotationMatrix = matrix::Convert(XMMatrixRotationAxis(vector3::GetSIMD(axis), delta));

		SetState(STATE::RIGHT, vector3::Convert(XMVector3TransformNormal(vector3::GetSIMD(vRight), matrix::GetSIMD(rotationMatrix))));
		SetState(STATE::UP,    vector3::Convert(XMVector3TransformNormal(vector3::GetSIMD(vUp),    matrix::GetSIMD(rotationMatrix))));
		SetState(STATE::LOOK,  vector3::Convert(XMVector3TransformNormal(vector3::GetSIMD(vLook),  matrix::GetSIMD(rotationMatrix))));
	}

	SharedPtr<Transform> Transform::Create(const COMPONENT_INIT_DESC* desc)
	{
		auto component = CreateSharedPtr<Transform>();

		ThrowIfFailed(component->Init(desc));

		return component;
	}
}