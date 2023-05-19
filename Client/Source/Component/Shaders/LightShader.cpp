#include "pch.h"
#include "LightShader.h"

namespace CLIENT
{
	HRESULT CLIENT::LightShader::Init(const COMPONENT_INIT_DESC* desc)
	{
		mInitDesc = *desc;

		return S_OK;
	}

	void CLIENT::LightShader::Render(ID3D11DeviceContext* context, i32 indexCount, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv)
	{
	}

	void CLIENT::LightShader::InitShader()
	{
	}

	void CLIENT::LightShader::SetShaderParameter(ID3D11DeviceContext* context, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv)
	{
	}

	void CLIENT::LightShader::RenderShader(ID3D11DeviceContext* context, i32 indexCount)
	{
	}

	SharedPtr<LightShader> LightShader::Create(const COMPONENT_INIT_DESC* desc)
	{
		auto component = CreateSharedPtr<LightShader>();

		ThrowIfFailed(component->Init(desc));

		return component;
	}
}