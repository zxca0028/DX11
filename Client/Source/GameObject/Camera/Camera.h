#pragma once

#include "GameObject/GameObject.h"

namespace CLIENT
{
	class Camera final : public GameObject
	{
	private:
		SharedPtr<class Transform> mTransform;
	public:
		virtual ~Camera() = default;
	public:
		virtual HRESULT Init(const OBJECT_INIT_DESC* desc) override;
	public:
		virtual void Update() override;
		virtual void Render() override;
	public:
		virtual void UpdateObject() override;
		virtual void RenderObject() override;
	public:
		static SharedPtr<Camera> Create(const OBJECT_INIT_DESC* desc = nullptr);
	};
}