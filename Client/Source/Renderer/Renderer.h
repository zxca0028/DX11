#pragma once

#include "Core.h"

namespace CLIENT
{
	class Renderer final : public ISingleton
	{
	public:
		virtual void Init() override;
	public:
		void Frame();
		void Render();
		void Destroy();
	private:
	private:
		SharedPtr<class Camera>        mCamera;
		SharedPtr<class Rect>          mRect;
		SharedPtr<class ColorShader>   mColorShader;
		SharedPtr<class TextureShader> mTextureShader;
	};
}