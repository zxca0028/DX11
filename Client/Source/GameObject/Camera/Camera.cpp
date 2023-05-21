#include "pch.h"
#include "Camera.h"
#include "Global/Pipeline.h"
#include "Component/Transform/Transform.h"

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

        return S_OK;
    }

    void CLIENT::Camera::Update()
    {
        vector3 vUp     = mTransform->GetState(Transform::STATE::UP);
        vector3 vLookAt = vector3(0.0f, 0.0f, 0.0f);

        matrix viewMatrix = matrix::Convert(XMMatrixLookAtLH(mTransform->GetState(Transform::STATE::POSITION).GetSIMD(), vLookAt.GetSIMD(), vUp.GetSIMD()));

        GlobalInstance::Instance<Pipeline>()->SetMatrix(Pipeline::STATE::VIEW, viewMatrix);

        /*vector3 vUp = vector3(0.0f, 1.0f, 0.0f);
        vector3 vLookAt = vector3(0.0f, 0.0f, 1.0f);

        f32 pitch = 0.f * 0.0174532925f;
        f32 yaw   = 0.f * 0.0174532925f;
        f32 roll  = 0.f * 0.0174532925f;

        matrix rotationMatrix = matrix::Convert(XMMatrixRotationRollPitchYaw(pitch, yaw, roll));

        vUp     = vector3::Convert(XMVector3TransformCoord(vUp.GetSIMD(), rotationMatrix.GetSIMD()));
        vLookAt = vector3::Convert(XMVector3TransformCoord(vLookAt.GetSIMD(), rotationMatrix.GetSIMD()));

        vLookAt = mPosition + vLookAt;


        GlobalInstance::Instance<Pipeline>()->SetMatrix
        (Pipeline::STATE::VIEW,matrix::Convert(XMMatrixLookAtLH(mTransform->GetState(Transform::STATE::POSITION).GetSIMD(), vLookAt.GetSIMD(), vUp.GetSIMD())));*/

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


