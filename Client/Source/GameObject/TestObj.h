#pragma once

#include "GameObject.h"

namespace CLIENT
{
	class TestObj1 final : public GameObject
	{
	private:
		vector3 mPosition;
	public:
		TestObj1() = default;
		TestObj1(vector3 v) : mPosition(v) {}
	private:
		SharedPtr<class Rect>          mRect;
		SharedPtr<class Texture>       mTexture;
		SharedPtr<class TextureShader> mShader;
	public:
		virtual void Init()   override;
		virtual void Update() override;
		virtual void Render() override;
	private:
		virtual void UpdateObject() override;
		virtual void RenderObject() override;
	};
}