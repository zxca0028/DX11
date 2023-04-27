#include "pch.h"
#include "Graphics.h"

namespace CLIENT
{
	void CLIENT::Graphics::Init()
	{
		mD3D = InitUniquePtr<D3D>();
	}

	void CLIENT::Graphics::Frame()
	{
		mD3D->Render();
	}

	void CLIENT::Graphics::Render()
	{
		mD3D->BeginScene();

		mD3D->EndScene();
	}

	void CLIENT::Graphics::Destroy()
	{
		mD3D->Destroy();
	}
}