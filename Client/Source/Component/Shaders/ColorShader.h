#pragma once

#include "Shader.h"

namespace CLIENT
{
	class ColorShader final : public Shader
	{
	public:
		virtual ~ColorShader() = default;
	protected:
		virtual HRESULT Init(const COMPONENT_INIT_DESC* desc) override;
	public:
		virtual void Render(ID3D11DeviceContext* context, i32 indexCount, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv) override;
	private:
		virtual void InitShader() override;
		virtual void RenderShader(ID3D11DeviceContext* context, i32 indexCount) override;
		void SetShaderParameter(ID3D11DeviceContext* context, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv);
	public:
		static SharedPtr<ColorShader> Create(const COMPONENT_INIT_DESC* desc = nullptr);
	};
}