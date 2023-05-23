#include "pch.h"
#include "Camera.h"
#include "Global/Pipeline.h"
#include "Component/Transform/Transform.h"
#include "Input/Input.h"

namespace CLIENT
{
    HRESULT Camera::Init(const OBJECT_INIT_DESC* desc)
    {
        mInitDesc = *desc;

        Component::COMPONENT_INIT_DESC transformInitDesc;
        {
            transformInitDesc.position = mInitDesc.position;
            mTransform = Transform::Create(&transformInitDesc);
        }

        f32 fieldOfView  = ToRadian(15.f);
        f32 screenAspect = (f32)gScreenWidth / (f32)gScreenHeight;

        matrix projMatrix = matrix::Convert(XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, 0.1f, 1000.0f));
        matrix orthMatrix = matrix::Convert(XMMatrixOrthographicLH((f32)gScreenWidth, (f32)gScreenHeight, 0.1f, 1000.0f));

        GlobalInstance::Instance<Pipeline>()->SetMatrix(Pipeline::STATE::PROJ, projMatrix);
        GlobalInstance::Instance<Pipeline>()->SetMatrix(Pipeline::STATE::ORTH, orthMatrix);

        return S_OK;
    }

    void CLIENT::Camera::Update()
    {
        if (GlobalInstance::Instance<Input>()->KeyInput(DIK_W))
        {
            mTransform->Move();
        }
        if (GlobalInstance::Instance<Input>()->KeyInput(DIK_S))
        {
            mTransform->Back();
        }
        if (GlobalInstance::Instance<Input>()->KeyInput(DIK_A))
        {
            mTransform->Left();
        }
        if (GlobalInstance::Instance<Input>()->KeyInput(DIK_D))
        {
            mTransform->Right();
        }
        if (GlobalInstance::Instance<Input>()->KeyInput(DIK_UPARROW))
        {
            mTransform->Up();
        }
        if (GlobalInstance::Instance<Input>()->KeyInput(DIK_DOWNARROW))
        {
            mTransform->Down();
        }

        

        i32 dx, dy;
        GlobalInstance::Instance<Input>()->MouseInput(dx, dy);


        vector3 vAxisY = vector3(0.0f, 1.0f, 0.0f);
        vector3 vAxisX = mTransform->GetState(Transform::STATE::RIGHT);
        

        matrix rotateMatrix1 = matrix::Convert(XMMatrixRotationAxis(vAxisY.GetSIMD(), dx * 0.001f));
        matrix rotateMatrix2 = matrix::Convert(XMMatrixRotationAxis(vAxisX.GetSIMD(), dy * 0.001f));

        matrix m1 = matrix::Convert(XMMatrixMultiply(mTransform->GetWorldMatrix().GetSIMD(), rotateMatrix1.GetSIMD()));
        matrix m2 = matrix::Convert(XMMatrixMultiply(m1.GetSIMD(), rotateMatrix2.GetSIMD()));

        mTransform->SetWorldMatrix(m2);

        vector3 vUp     = mTransform->GetState(Transform::STATE::UP);
        vector3 vLookAt = mTransform->GetState(Transform::STATE::POSITION) + mTransform->GetState(Transform::STATE::LOOK);

        matrix viewMatrix = matrix::Convert(XMMatrixLookAtLH(mTransform->GetState(Transform::STATE::POSITION).GetSIMD(), vLookAt.GetSIMD(), vUp.GetSIMD()));

        GlobalInstance::Instance<Pipeline>()->SetMatrix(Pipeline::STATE::VIEW, viewMatrix);
    }

    void Camera::Render()
    {
    }

    void Camera::UpdateObject()
    {
    }

    void Camera::RenderObject()
    {
    }

    SharedPtr<Camera> Camera::Create(const OBJECT_INIT_DESC* desc)
    {
        auto object = CreateSharedPtr<Camera>();

        ThrowIfFailed(object->Init(desc));

        return object;
    }
}


