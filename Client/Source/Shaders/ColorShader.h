#pragma once

#include "Core.h"

namespace CLIENT
{
	class ColorShader
	{
	private:
		struct MatrixBufferType
		{
			XMMATRIX worldMatrix;
			XMMATRIX viewMatrix;
			XMMATRIX projMatrix;
		};
	private:
		ID3D11VertexShader* mVertexShader;
		ID3D11PixelShader*  mPixelShader;
		ID3D11InputLayout*  mLayout;
		ID3D11Buffer*       mMatrixBuffer;
	public:
		void Init(ID3D11Device* device, HWND hWnd);
		void Render(ID3D11DeviceContext* context, i32 indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projMatrix);
	private:
		void InitShader(ID3D11Device* device, HWND hWnd, const wstring& Filename);
		void SetShaderParameters(ID3D11DeviceContext* context, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projMatrix);
		void RenderShader(ID3D11DeviceContext* context, i32 indexCount);
	};
}