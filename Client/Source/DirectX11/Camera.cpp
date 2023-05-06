#include "pch.h"
#include "Camera.h"

namespace CLIENT
{
    void CLIENT::Camera::SetPosition(f32 x, f32 y, f32 z)
    {
		mPosition.x = x; mPosition.y = y; mPosition.z = z;
    }

    void CLIENT::Camera::SetRotation(f32 x, f32 y, f32 z)
    {
        mRotation.x = x; mRotation.y = y; mRotation.z = z;
    }

    vector3 CLIENT::Camera::GetPosition()
    {
        return mPosition;
    }

    vector3 CLIENT::Camera::GetRotation()
    {
        return mRotation;
    }

    void CLIENT::Camera::GetViewMatrix(matrix& viewMatrix)
    {
        viewMatrix = mViewMatrix;
    }

    void CLIENT::Camera::Render()
    {
        vector3 vUp       = vector3(0.0f, 1.0f, 0.0f);
        vector3 vLookAt   = vector3(0.0f, 0.0f, 1.0f);

        f32 pitch = mRotation.x * 0.0174532925f;
        f32 yaw   = mRotation.y * 0.0174532925f;
        f32 roll  = mRotation.z * 0.0174532925f;

        matrix rotationMatrix = matrix::RotationRollPitchYaw(pitch, yaw, roll);

        vUp     = vector3::TransformCoord(vUp,     rotationMatrix);
        vLookAt = vector3::TransformCoord(vLookAt, rotationMatrix);

        vLookAt = mPosition + vLookAt;

        mViewMatrix = matrix::Convert(XMMatrixLookAtLH(mPosition.GetSIMD(), vLookAt.GetSIMD(), vUp.GetSIMD()));
    }
}


