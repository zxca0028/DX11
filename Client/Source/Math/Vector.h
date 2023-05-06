#pragma once

#include "Math/Matrix.h"

namespace CLIENT
{
	class vector2 final
	{
	private:
		float x, y;
	public:
		vector2() : x(0), y(0) {}
		vector2(float x, float y) : x(x), y(y) {}
	};

	class vector3 final
	{
	public:
		float x, y, z;
	public:
		vector3() : x(0), y(0), z(0) {}
		vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	public:
		inline vector3 operator + (const vector3& v) const
		{
			return vector3(x + v.x, y + v.y, z + v.z);
		}
	public:
		XMVECTOR GetSIMD()
		{
			XMFLOAT3 v = XMFLOAT3(x, y, z);

			return XMLoadFloat3(&v);
		}
	public:
		inline static vector3 TransformCoord(vector3 v, matrix m)
		{
			XMVECTOR xv = XMVector3TransformCoord(v.GetSIMD(), m.GetSIMD());

			XMFLOAT3 v3;

			XMStoreFloat3(&v3, xv);

			return vector3(v3.x, v3.y, v3.z);
		}
	};
}