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
            mTransform->Move(0.001f);
        }
        if (GlobalInstance::Instance<Input>()->KeyInput(DIK_S))
        {
            mTransform->Back(0.001f);
        }
        if (GlobalInstance::Instance<Input>()->KeyInput(DIK_A))
        {
            mTransform->Left(0.001f);
        }
        if (GlobalInstance::Instance<Input>()->KeyInput(DIK_D))
        {
            mTransform->Right(0.001f);
        }
        if (GlobalInstance::Instance<Input>()->KeyInput(DIK_UPARROW))
        {
            mTransform->Up(0.001f);
        }
        if (GlobalInstance::Instance<Input>()->KeyInput(DIK_DOWNARROW))
        {
            mTransform->Down(0.001f);
        }

        //POINT pos = { gScreenWidth / 2, gScreenHeight / 2 };
        //ClientToScreen(ghWnd, &pos);
        //SetCursorPos(pos.x, pos.y);

        mTransform->RotationAxis(vector3::Y(), GlobalInstance::Instance<Input>()->MouseInput(Input::STATE::X) * 0.001f);
        mTransform->RotationAxis(mTransform->GetState(Transform::STATE::RIGHT), GlobalInstance::Instance<Input>()->MouseInput(Input::STATE::Y) * 0.001f);

        matrix viewMatrix = mTransform->GetWorldMatrixInv();
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


