#pragma once

#include "Shader.h"

namespace CLIENT
{
	class LightShader final : public Shader
	{
	private:
		struct LightBufferType
		{
			vector4 diffuseColor;
			vector3 lightDirection;
			float   padding;
		};
	private:
		ID3D11Buffer* mLightBuffer;
	public:
		virtual ~LightShader() = default;
	protected:
		virtual HRESULT Init(const COMPONENT_INIT_DESC* desc) override;
	public:
		virtual void Render(ID3D11DeviceContext* context, i32 indexCount, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv) override;
	private:
		virtual void InitShader() override;
		virtual void RenderShader(ID3D11DeviceContext* context, i32 indexCount) override;
		void SetShaderParameter(ID3D11DeviceContext* context, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv, vector3 lightDirection, vector4 diffuseColor);
	public:
		static SharedPtr<LightShader> Create(const COMPONENT_INIT_DESC* desc = nullptr);
	};
}
