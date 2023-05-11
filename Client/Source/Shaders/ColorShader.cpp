#include "pch.h"
#include "ColorShader.h"

namespace CLIENT
{
	void CLIENT::ColorShader::Init(ID3D11Device* device, HWND hWnd)
	{
		InitShader(device, hWnd, L"Color.hlsl");
	}

	void CLIENT::ColorShader::Render(ID3D11DeviceContext* context, i32 indexCount, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv)
	{
		SetShaderParameter(context, worldMatrix, viewMatrix, projMatrix, nullptr);

		RenderShader(context, indexCount);
	}

	void CLIENT::ColorShader::InitShader(ID3D11Device* device, HWND hWnd, const wstring& fileName)
	{
		u32 compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG) 
		compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		HRESULT result;
		wstring shaderDirectory = L"../Source/Shaders/" + fileName;

		ComPtr<ID3DBlob> errorMessage;
		ComPtr<ID3DBlob> vertexShaderBuffer;
		ComPtr<ID3DBlob> pixelShaderBuffer;

		ThrowIfFailed(D3DCompileFromFile(shaderDirectory.c_str(), nullptr, nullptr, "ColorVertexShader", "vs_5_0", compileFlags, 0, &vertexShaderBuffer, &errorMessage));
		ThrowIfFailed(device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &mVertexShader));

		ThrowIfFailed(D3DCompileFromFile(shaderDirectory.c_str(), nullptr, nullptr, "ColorPixelShader", "ps_5_0", compileFlags, 0, &pixelShaderBuffer, &errorMessage));
		ThrowIfFailed(device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),   pixelShaderBuffer->GetBufferSize(),  nullptr, &mPixelShader));

		D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
		{
			polygonLayout[0].SemanticName         = "POSITION";
			polygonLayout[0].SemanticIndex        = 0;
			polygonLayout[0].Format               = DXGI_FORMAT_R32G32B32_FLOAT;
			polygonLayout[0].InputSlot            = 0;
			polygonLayout[0].AlignedByteOffset    = 0;
			polygonLayout[0].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
			polygonLayout[0].InstanceDataStepRate = 0;

			polygonLayout[1].SemanticName         = "COLOR";
			polygonLayout[1].SemanticIndex        = 0;
			polygonLayout[1].Format               = DXGI_FORMAT_R32G32B32A32_FLOAT;
			polygonLayout[1].InputSlot            = 0;
			polygonLayout[1].AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
			polygonLayout[1].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
			polygonLayout[1].InstanceDataStepRate = 0;

			u32 numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

			ThrowIfFailed(device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &mLayout));
		}

		D3D11_BUFFER_DESC matrixBufferDesc;
		{
			matrixBufferDesc.Usage               = D3D11_USAGE_DYNAMIC;
			matrixBufferDesc.ByteWidth           = sizeof(MatrixBufferType);
			matrixBufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
			matrixBufferDesc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
			matrixBufferDesc.MiscFlags           = 0;
			matrixBufferDesc.StructureByteStride = 0;

			ThrowIfFailed(device->CreateBuffer(&matrixBufferDesc, nullptr, &mMatrixBuffer));
		}
	}

	void CLIENT::ColorShader::SetShaderParameter(ID3D11DeviceContext* context, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;

		ThrowIfFailed(context->Map(mMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));

		MatrixBufferType* dataPtr = (MatrixBufferType*)mappedResource.pData;

		dataPtr->worldMatrix = matrix::Convert(XMMatrixTranspose(worldMatrix.GetSIMD()));
		dataPtr->viewMatrix  = matrix::Convert(XMMatrixTranspose(viewMatrix.GetSIMD()));
		dataPtr->projMatrix  = matrix::Convert(XMMatrixTranspose(projMatrix.GetSIMD()));

		context->Unmap(mMatrixBuffer, 0);

		u32 bufferNumber = 0;

		context->VSSetConstantBuffers(bufferNumber, 1, &mMatrixBuffer);
	}

	void CLIENT::ColorShader::RenderShader(ID3D11DeviceContext* context, i32 indexCount)
	{
		context->IASetInputLayout(mLayout);

		context->VSSetShader(mVertexShader, nullptr, 0);
		context->PSSetShader(mPixelShader,  nullptr, 0);

		context->DrawIndexed(indexCount, 0, 0);
	}
}