#include "pch.h"
#include "Rect.h"
#include "DirectX11/D3D.h"

namespace CLIENT
{
	HRESULT CLIENT::Rect::Init(const COMPONENT_INIT_DESC* desc)
	{
		ThrowIfFailed(InitBuffer());

		return S_OK;
	}

	void CLIENT::Rect::Render()
	{
		RenderBuffer();
	}

	HRESULT CLIENT::Rect::InitBuffer()
	{
		mVertexCount = 4;
		mIndexCount  = 6;

		VertexTexType* vertices = new VertexTexType[mVertexCount];
		{
			vertices[0].position = vector3(-0.5f, 0.5f, 0.0f);
			vertices[0].texture  = vector2(0.0f, 0.0f);
			vertices[0].normal   = vector3(0.0f, 0.0f, -1.0f);

			vertices[1].position = vector3(0.5f, 0.5f, 0.0f);
			vertices[1].texture  = vector2(1.0f, 0.0f);
			vertices[1].normal   = vector3(0.0f, 0.0f, -1.0f);

			vertices[2].position = vector3(0.5f, -0.5f, 0.0f);
			vertices[2].texture  = vector2(1.0f, 1.0f);
			vertices[2].normal   = vector3(0.0f, 0.0f, -1.0f);

			vertices[3].position = vector3(-0.5f, -0.5f, 0.0f);
			vertices[3].texture  = vector2(0.0f, 1.0f);
			vertices[3].normal   = vector3(0.0f, 0.0f, -1.0f);
		}

		u32* indices = new u32[mIndexCount];
		{
			indices[0] = 0;	indices[1] = 1;	indices[2] = 2;
			indices[3] = 0;	indices[4] = 2;	indices[5] = 3;
		}

		D3D11_BUFFER_DESC vectexTexBufferDesc;
		{
			vectexTexBufferDesc.Usage               = D3D11_USAGE_DEFAULT;
			vectexTexBufferDesc.ByteWidth           = sizeof(VertexTexType) * mVertexCount;
			vectexTexBufferDesc.BindFlags           = D3D11_BIND_VERTEX_BUFFER;
			vectexTexBufferDesc.CPUAccessFlags      = 0;
			vectexTexBufferDesc.MiscFlags           = 0;
			vectexTexBufferDesc.StructureByteStride = 0;
		}

		D3D11_SUBRESOURCE_DATA vertexTexData;
		{
			vertexTexData.pSysMem          = vertices;
			vertexTexData.SysMemPitch      = 0;
			vertexTexData.SysMemSlicePitch = 0;
		}

		ThrowIfFailed(GlobalInstance::Instance<D3D>()->GetDevice()->CreateBuffer(&vectexTexBufferDesc, &vertexTexData, &mVertexBuffer));

		D3D11_BUFFER_DESC indexTexBufferDesc;
		{
			indexTexBufferDesc.Usage               = D3D11_USAGE_DEFAULT;
			indexTexBufferDesc.ByteWidth           = sizeof(u32) * mIndexCount;
			indexTexBufferDesc.BindFlags           = D3D11_BIND_INDEX_BUFFER;
			indexTexBufferDesc.CPUAccessFlags      = 0;
			indexTexBufferDesc.MiscFlags           = 0;
			indexTexBufferDesc.StructureByteStride = 0;
		}

		D3D11_SUBRESOURCE_DATA indexTexData;
		{
			indexTexData.pSysMem          = indices;
			indexTexData.SysMemPitch      = 0;
			indexTexData.SysMemSlicePitch = 0;
		}

		ThrowIfFailed(GlobalInstance::Instance<D3D>()->GetDevice()->CreateBuffer(&indexTexBufferDesc, &indexTexData, &mIndexBuffer));

		delete[] vertices;
		vertices = 0;

		delete[] indices;
		indices = 0;

		return S_OK;
	}

	void CLIENT::Rect::RenderBuffer()
	{
		u32 stride = sizeof(VertexTexType);
		u32 offset = 0;

		GlobalInstance::Instance<D3D>()->GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
		GlobalInstance::Instance<D3D>()->GetDeviceContext()->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		GlobalInstance::Instance<D3D>()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	SharedPtr<Rect> Rect::Create(const COMPONENT_INIT_DESC* desc)
	{
		auto component = CreateSharedPtr<Rect>();

		ThrowIfFailed(component->Init(desc));

		return component;
	}
}