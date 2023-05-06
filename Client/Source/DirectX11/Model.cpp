#include "pch.h"
#include "Model.h"

namespace CLIENT
{
	void CLIENT::Model::Init(ID3D11Device* device)
	{
		InitBuffers(device);
	}

	void CLIENT::Model::Render(ID3D11DeviceContext* context)
	{
		RenderBuffers(context);
	}

	void CLIENT::Model::InitBuffers(ID3D11Device* device)
	{
		mVertexCount = 4;
		mIndexCount  = 6;

		VertexType* vertices = new VertexType[mVertexCount];
		{
			vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
			vertices[0].color    = XMFLOAT4( 0.0f,  1.0f, 0.0f, 1.0f);

			vertices[1].position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
			vertices[1].color    = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

			vertices[2].position = XMFLOAT3(1.0f, 1.0f, 0.0f);
			vertices[2].color    = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

			vertices[3].position = XMFLOAT3(1.0f, -1.0f, 0.0f);
			vertices[3].color    = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		}
		
		u32* indices = new u32[mIndexCount];
		{
			indices[0] = 0;
			indices[1] = 1;
			indices[2] = 2;
			indices[3] = 0;
			indices[4] = 2;
			indices[5] = 3;
		}

		D3D11_BUFFER_DESC vertexBufferDesc;
		{
			vertexBufferDesc.Usage				 = D3D11_USAGE_DEFAULT;
			vertexBufferDesc.ByteWidth			 = sizeof(VertexType) * mVertexCount;
			vertexBufferDesc.BindFlags			 = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDesc.CPUAccessFlags		 = 0;
			vertexBufferDesc.MiscFlags			 = 0;
			vertexBufferDesc.StructureByteStride = 0;
		}
		D3D11_SUBRESOURCE_DATA vertexData;
		{
			vertexData.pSysMem          = vertices;
			vertexData.SysMemPitch      = 0;
			vertexData.SysMemSlicePitch = 0;
		}

		ThrowIfFailed(device->CreateBuffer(&vertexBufferDesc, &vertexData, &mVertexBuffer));

		D3D11_BUFFER_DESC indexBufferDesc;
		{
			indexBufferDesc.Usage               = D3D11_USAGE_DEFAULT;
			indexBufferDesc.ByteWidth           = sizeof(u32) * mIndexCount;
			indexBufferDesc.BindFlags           = D3D11_BIND_INDEX_BUFFER;
			indexBufferDesc.CPUAccessFlags      = 0;
			indexBufferDesc.MiscFlags           = 0;
			indexBufferDesc.StructureByteStride = 0;
		}
		D3D11_SUBRESOURCE_DATA indexData;
		{
			indexData.pSysMem          = indices;
			indexData.SysMemPitch      = 0;
			indexData.SysMemSlicePitch = 0;
		}

		ThrowIfFailed(device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer));

		delete[] vertices;
		vertices = 0;

		delete[] indices;
		indices = 0;
	}

	void CLIENT::Model::RenderBuffers(ID3D11DeviceContext* context)
	{
		u32 stride = sizeof(VertexType);
		u32 offset = 0;

		context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
		context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}