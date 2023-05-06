#pragma once

#include "Core.h"

namespace CLIENT
{
	class Camera
	{
	private:
		vector3 mPosition;
		vector3 mRotation;
		matrix  mViewMatrix;
	public:
		void SetPosition(f32 x, f32 y, f32 z);
		void SetRotation(f32 x, f32 y, f32 z);
	public:
		vector3 GetPosition();
		vector3 GetRotation();
		void GetViewMatrix(matrix& viewMatrix);
	public:
		void Render();
	};
}