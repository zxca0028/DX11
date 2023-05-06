#pragma once

#include "Core.h"

namespace CLIENT
{
	class TextureShader
	{
	private:
		struct MatrixBufferType
		{
			matrix worldMatrix;
			matrix viewMatrix;
			matrix projMatrix;
		};
	private:
		ID3D11VertexShader* mVertexShader;
		ID3D11PixelShader*  mPixelShader;
		ID3D11InputLayout*  mLayout;
		ID3D11Buffer*       mMatrixBuffer;
	private:
		ID3D11SamplerState* mSamplerState;
	public:
		void Init(ID3D11Device* device, HWND hWnd);
		void Render(ID3D11DeviceContext* context, i32 indexCount, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv);
	private:
		void InitShader(ID3D11Device* device, HWND hWnd, const wstring& fileName);
		void SetShaderParameter(ID3D11DeviceContext* context, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv);
		void RenderShader(ID3D11DeviceContext* context, i32 indexCount);
	};
}