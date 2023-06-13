#include "pch.h"
#include "Cube.h"
#include "DirectX11/D3D.h"

namespace CLIENT
{
    HRESULT Cube::Init(const COMPONENT_INIT_DESC* desc)
    {
        ThrowIfFailed(InitBuffer());

        return S_OK;
    }

    void Cube::Render()
    {
        RenderBuffer();
    }

    HRESULT Cube::InitBuffer()
    {
        std::ifstream fin;

        byte* fileName = "../Resource/Text/cube.txt";

        fin.open(fileName);

        byte input;

        fin.get(input);
        while (input != ':')
        {
            fin.get(input);
        }
        fin >> mVertexCount;
        mIndexCount = mVertexCount;

        mModelType = new ModelType[mVertexCount];

        fin.get(input);
        while (input != ':')
        {
            fin.get(input);
        }
        fin.get(input);
        fin.get(input);

        for (i32 i = 0; i < mVertexCount; ++i)
        {
            fin >> mModelType[i].x >> mModelType[i].y >> mModelType[i].z;
            fin >> mModelType[i].u >> mModelType[i].v;
            fin >> mModelType[i].nx >> mModelType[i].ny >> mModelType[i].nz;
        }

        fin.close();

        VertexTexType* vertices = new VertexTexType[mVertexCount];
        {
            for (i32 i = 0; i < mVertexCount; ++i)
            {
                vertices[i].position = vector3(mModelType[i].x,  mModelType[i].y,  mModelType[i].z);
                vertices[i].texture  = vector2(mModelType[i].u,  mModelType[i].v);
                vertices[i].normal   = vector3(mModelType[i].nx, mModelType[i].ny, mModelType[i].nz);
            }
        }

        u32* indices = new u32[mIndexCount];
        {
            for (i32 i = 0; i < mIndexCount; ++i)
            {
                indices[i] = i;
            }
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

        delete[] mModelType;
        mModelType = 0;

        return S_OK;
    }

    void CLIENT::Cube::RenderBuffer()
    {
        u32 stride = sizeof(VertexTexType);
        u32 offset = 0;

        GlobalInstance::Instance<D3D>()->GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
        GlobalInstance::Instance<D3D>()->GetDeviceContext()->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
        GlobalInstance::Instance<D3D>()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

    SharedPtr<Cube> Cube::Create(const COMPONENT_INIT_DESC* desc)
    {
        auto component = CreateSharedPtr<Cube>();

        ThrowIfFailed(component->Init(desc));

        return component;
    }
}