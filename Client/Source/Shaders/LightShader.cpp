#include "pch.h"
#include "LightShader.h"

namespace CLIENT
{
	void CLIENT::LightShader::Init(ID3D11Device* device, HWND hWnd)
	{
	}

	void CLIENT::LightShader::Render(ID3D11DeviceContext* context, i32 indexCount, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv)
	{
	}

	void CLIENT::LightShader::InitShader(ID3D11Device* device, HWND hWnd, const wstring& fileName)
	{
	}

	void CLIENT::LightShader::SetShaderParameter(ID3D11DeviceContext* context, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv)
	{
	}

	void CLIENT::LightShader::RenderShader(ID3D11DeviceContext* context, i32 indexCount)
	{
	}
}