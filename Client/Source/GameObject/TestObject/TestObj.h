#pragma once

#include "GameObject/GameObject.h"

namespace CLIENT
{
	class TestObj final : public GameObject 
	{
	private:
		SharedPtr<class Rect>          mRect;
		SharedPtr<class Texture>       mTexture;
		SharedPtr<class TextureShader> mShader;
	public:
		virtual ~TestObj() = default;
	public:
		virtual HRESULT Init(const OBJECT_INIT_DESC& desc)   override;
	public:
		virtual void Update() override;
		virtual void Render() override;
	private:
		virtual void UpdateObject() override;
		virtual void RenderObject() override;
	public:
		static SharedPtr<TestObj> Create(const OBJECT_INIT_DESC& desc);
	};
}