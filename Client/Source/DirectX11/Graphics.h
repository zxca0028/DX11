#pragma once

#include "Core.h"

namespace CLIENT
{
	class Graphics
	{
	public:
		void Init();
		void Frame();
		void Render();
		void Destroy();
	private:
		SharedPtr<class D3D>           mD3D;
		SharedPtr<class Camera>        mCamera;
		SharedPtr<class Model>         mModel;
		SharedPtr<class ColorShader>   mColorShader;
		SharedPtr<class TextureShader> mTextureShader;
	};
}