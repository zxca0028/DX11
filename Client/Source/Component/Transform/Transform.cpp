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
		switch (state)
		{
		case STATE::RIGHT:
			return vector3(mWorldMatrix._11, mWorldMatrix._12, mWorldMatrix._13);

		case STATE::UP:
			return vector3(mWorldMatrix._21, mWorldMatrix._22, mWorldMatrix._23);

		case STATE::LOOK:
			return vector3(mWorldMatrix._31, mWorldMatrix._32, mWorldMatrix._33);

		case STATE::POSITION:
			return vector3(mWorldMatrix._41, mWorldMatrix._42, mWorldMatrix._43);
		}
	}

	void Transform::SetState(STATE state, vector3 v)
	{
		switch (state)
		{
		case STATE::RIGHT:
			mWorldMatrix._11 = v.x; mWorldMatrix._12 = v.y; mWorldMatrix._13 = v.z;

		case STATE::UP:
			mWorldMatrix._21 = v.x; mWorldMatrix._22 = v.y; mWorldMatrix._23 = v.z;

		case STATE::LOOK:
			mWorldMatrix._31 = v.x; mWorldMatrix._32 = v.y; mWorldMatrix._33 = v.z;

		case STATE::POSITION:
			mWorldMatrix._41 = v.x; mWorldMatrix._42 = v.y; mWorldMatrix._43 = v.z;
		}
	}

	void Transform::Move()
	{
		//mWorldMatrix._43 += 0.01f;
		mWorldMatrix._41 += GetState(STATE::LOOK).x * 0.01f;
		mWorldMatrix._42 += GetState(STATE::LOOK).y * 0.01f;
		mWorldMatrix._43 += GetState(STATE::LOOK).z * 0.01f;
	}

	void Transform::Back()
	{
		mWorldMatrix._41 -= GetState(STATE::LOOK).x * 0.01f;
		mWorldMatrix._42 -= GetState(STATE::LOOK).y * 0.01f;
		mWorldMatrix._43 -= GetState(STATE::LOOK).z * 0.01f;
	}

	void Transform::Left()
	{
		mWorldMatrix._41 -= GetState(STATE::RIGHT).x * 0.01f;
		mWorldMatrix._42 -= GetState(STATE::RIGHT).y * 0.01f;
		mWorldMatrix._43 -= GetState(STATE::RIGHT).z * 0.01f;
	}

	void Transform::Right()
	{
		mWorldMatrix._41 += GetState(STATE::RIGHT).x * 0.01f;
		mWorldMatrix._42 += GetState(STATE::RIGHT).y * 0.01f;
		mWorldMatrix._43 += GetState(STATE::RIGHT).z * 0.01f;
	}

	void Transform::Up()
	{
		mWorldMatrix._41 += GetState(STATE::UP).x * 0.01f;
		mWorldMatrix._42 += GetState(STATE::UP).y * 0.01f;
		mWorldMatrix._43 += GetState(STATE::UP).z * 0.01f;
	}

	void Transform::Down()
	{
		mWorldMatrix._41 -= GetState(STATE::UP).x * 0.01f;
		mWorldMatrix._42 -= GetState(STATE::UP).y * 0.01f;
		mWorldMatrix._43 -= GetState(STATE::UP).z * 0.01f;
	}

	SharedPtr<Transform> Transform::Create(const COMPONENT_INIT_DESC* desc)
	{
		auto component = CreateSharedPtr<Transform>();

		ThrowIfFailed(component->Init(desc));

		return component;
	}
}