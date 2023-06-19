#include "pch.h"
#include "LightShader.h"
#include "DirectX11/D3D.h"

namespace CLIENT
{
	HRESULT CLIENT::LightShader::Init(const COMPONENT_INIT_DESC* desc)
	{
		if (nullptr != desc)
		{
			mInitDesc = *desc;
		}

		InitShader();

		return S_OK;
	}

	void CLIENT::LightShader::Render(ID3D11DeviceContext* context, i32 indexCount, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv)
	{
		SetShaderParameter(context, worldMatrix, viewMatrix, projMatrix, srv, vector3(1.f,0.f,1.f),vector4(0.f,0.f,1.f,1.f));

		RenderShader(context, indexCount);
	}

	void CLIENT::LightShader::InitShader()
	{
		u32 compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG) 
		compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		wstring shaderDirectory = L"../Source/Component/Shaders/HLSL/" + mInitDesc.path;

		ComPtr<ID3DBlob> errorMessage;
		ComPtr<ID3DBlob> vertexShaderBuffer;
		ComPtr<ID3DBlob> pixelShaderBuffer;

		ThrowIfFailed(D3DCompileFromFile(shaderDirectory.c_str(), nullptr, nullptr, "LightVertexShader", "vs_5_0", compileFlags, 0, &vertexShaderBuffer, &errorMessage));
		ThrowIfFailed(GlobalInstance::Instance<D3D>()->GetDevice()->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &mVertexShader));

		ThrowIfFailed(D3DCompileFromFile(shaderDirectory.c_str(), nullptr, nullptr, "LightPixelShader", "ps_5_0", compileFlags, 0, &pixelShaderBuffer, &errorMessage));
		ThrowIfFailed(GlobalInstance::Instance<D3D>()->GetDevice()->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &mPixelShader));

		D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
		{
			polygonLayout[0].SemanticName         = "POSITION";
			polygonLayout[0].SemanticIndex        = 0;
			polygonLayout[0].Format               = DXGI_FORMAT_R32G32B32_FLOAT;
			polygonLayout[0].InputSlot            = 0;
			polygonLayout[0].AlignedByteOffset    = 0;
			polygonLayout[0].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
			polygonLayout[0].InstanceDataStepRate = 0;

			polygonLayout[1].SemanticName         = "TEXCOORD";
			polygonLayout[1].SemanticIndex        = 0;
			polygonLayout[1].Format               = DXGI_FORMAT_R32G32_FLOAT;
			polygonLayout[1].InputSlot            = 0;
			polygonLayout[1].AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
			polygonLayout[1].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
			polygonLayout[1].InstanceDataStepRate = 0;

			polygonLayout[2].SemanticName         = "NORMAL";
			polygonLayout[2].SemanticIndex        = 0;
			polygonLayout[2].Format               = DXGI_FORMAT_R32G32B32_FLOAT;
			polygonLayout[2].InputSlot            = 0;
			polygonLayout[2].AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
			polygonLayout[2].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
			polygonLayout[2].InstanceDataStepRate = 0;

			u32 numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);
				
			ThrowIfFailed(GlobalInstance::Instance<D3D>()->GetDevice()->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &mLayout));
		}

		D3D11_BUFFER_DESC matrixBufferDesc;
		{
			matrixBufferDesc.Usage               = D3D11_USAGE_DYNAMIC;
			matrixBufferDesc.ByteWidth           = sizeof(MatrixBufferType);
			matrixBufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
			matrixBufferDesc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
			matrixBufferDesc.MiscFlags           = 0;
			matrixBufferDesc.StructureByteStride = 0;

			ThrowIfFailed(GlobalInstance::Instance<D3D>()->GetDevice()->CreateBuffer(&matrixBufferDesc, nullptr, &mMatrixBuffer));
		}

		D3D11_SAMPLER_DESC samplerDesc;
		{
			samplerDesc.Filter         = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.MipLODBias     = 0.0f;
			samplerDesc.MaxAnisotropy  = 1;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			samplerDesc.BorderColor[0] = 0;
			samplerDesc.BorderColor[1] = 0;
			samplerDesc.BorderColor[2] = 0;
			samplerDesc.BorderColor[3] = 0;
			samplerDesc.MinLOD         = 0;
			samplerDesc.MaxLOD         = D3D11_FLOAT32_MAX;

			ThrowIfFailed(GlobalInstance::Instance<D3D>()->GetDevice()->CreateSamplerState(&samplerDesc, &mSamplerState));
		}

		D3D11_BUFFER_DESC lightBufferDesc;
		{
			lightBufferDesc.Usage               = D3D11_USAGE_DYNAMIC;
			lightBufferDesc.ByteWidth           = sizeof(LightBufferType);
			lightBufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
			lightBufferDesc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
			lightBufferDesc.MiscFlags           = 0;
			lightBufferDesc.StructureByteStride = 0;

			ThrowIfFailed(GlobalInstance::Instance<D3D>()->GetDevice()->CreateBuffer(&lightBufferDesc, nullptr, &mLightBuffer));
		}
	}

	void CLIENT::LightShader::SetShaderParameter(ID3D11DeviceContext* context, matrix worldMatrix, matrix viewMatrix, matrix projMatrix, ID3D11ShaderResourceView* srv, vector3 lightDirection, vector4 diffuseColor)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;

		ThrowIfFailed(context->Map(mMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));

		MatrixBufferType* matrixDataPtr = (MatrixBufferType*)mappedResource.pData;

		matrixDataPtr->worldMatrix = matrix::Convert(XMMatrixTranspose(matrix::GetSIMD(worldMatrix)));
		matrixDataPtr->viewMatrix  = matrix::Convert(XMMatrixTranspose(matrix::GetSIMD(viewMatrix)));
		matrixDataPtr->projMatrix  = matrix::Convert(XMMatrixTranspose(matrix::GetSIMD(projMatrix)));

		context->Unmap(mMatrixBuffer, 0);

		u32 matrixBufferNumber = 0;

		context->VSSetConstantBuffers(matrixBufferNumber, 1, &mMatrixBuffer);
		context->PSSetShaderResources(0, 1, &srv);

		ThrowIfFailed(context->Map(mLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));
		
		LightBufferType* lightDataPtr = (LightBufferType*)mappedResource.pData;

		lightDataPtr->diffuseColor   = diffuseColor;
		lightDataPtr->lightDirection = lightDirection;
		lightDataPtr->padding        = 0.0f;

		context->Unmap(mLightBuffer, 0);

		u32 lightBufferNumber = 0;

		context->PSSetConstantBuffers(lightBufferNumber, 1, &mLightBuffer);
	}

	void CLIENT::LightShader::RenderShader(ID3D11DeviceContext* context, i32 indexCount)
	{
		context->IASetInputLayout(mLayout);

		context->VSSetShader(mVertexShader, nullptr, 0);
		context->PSSetShader(mPixelShader, nullptr, 0);

		context->PSSetSamplers(0, 1, &mSamplerState);

		context->DrawIndexed(indexCount, 0, 0);
	}

	SharedPtr<LightShader> LightShader::Create(const COMPONENT_INIT_DESC* desc)
	{
		auto component = CreateSharedPtr<LightShader>();

		ThrowIfFailed(component->Init(desc));

		return component;
	}
}