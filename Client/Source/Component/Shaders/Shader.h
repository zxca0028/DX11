#pragma once

#include "Component/Component.h"

namespace CLIENT
{
	class Shader abstract : public Component
	{
	protected:
		struct MatrixBufferType
		{
			matrix worldMatrix;
			matrix viewMatrix;
			matrix projMatrix;
		};
	protected:
		ID3D11VertexShader* mVertexShader = nullptr;
		ID3D11PixelShader*  mPixelShader  = nullptr;
		ID3D11InputLayout*  mLayout       = nullptr;
		ID3D11Buffer*       mMatrixBuffer = nullptr;
	protected:
		virtual ~Shader() = default;
	public:
		virtual void Init(ID3D11Device* device, HWND hWnd) = 0;
		virtual void Render(ID3D11DeviceContext* context, i32 indexCount, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv) = 0;
	protected:
		virtual void InitShader(ID3D11Device* device, HWND hWnd, const wstring& fileName) = 0;
		virtual void SetShaderParameter(ID3D11DeviceContext* context, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv) = 0;
		virtual void RenderShader(ID3D11DeviceContext* context, i32 indexCount) = 0;
	};
}



