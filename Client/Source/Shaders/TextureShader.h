#pragma once

#include "Shader.h"

namespace CLIENT
{
	class TextureShader final : public Shader
	{
	private:
		ID3D11SamplerState* mSamplerState;
	public:
		virtual void Init(ID3D11Device* device, HWND hWnd) override;
		virtual void Render(ID3D11DeviceContext* context, i32 indexCount, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv) override;
	private:
		virtual void InitShader(ID3D11Device* device, HWND hWnd, const wstring& fileName) override;
		virtual void SetShaderParameter(ID3D11DeviceContext* context, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv) override;
		virtual void RenderShader(ID3D11DeviceContext* context, i32 indexCount) override;
	};
}