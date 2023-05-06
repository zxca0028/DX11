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
		vector2(XMFLOAT2 v) : x(v.x), y(v.y) {}
	public:
		inline vector2 operator + (const vector2& v) const
		{
			return vector2(x + v.x, y + v.y);
		}
	public:
		XMVECTOR GetSIMD()
		{
			XMFLOAT2 v = XMFLOAT2(x, y);

			return XMLoadFloat2(&v);
		}
	public:
		inline static vector2 Convert(XMVECTOR xv)
		{
			XMFLOAT2 v; XMStoreFloat2(&v, xv);

			return vector2(v);
		}
	};

	class vector3 final
	{
	public:
		float x, y, z;
	public:
		vector3() : x(0), y(0), z(0) {}
		vector3(float x, float y, float z) : x(x), y(y), z(z) {}
		vector3(XMFLOAT3 v) : x(v.x), y(v.y), z(v.z) {}
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
		inline static vector3 Convert(XMVECTOR xv)
		{
			XMFLOAT3 v;	XMStoreFloat3(&v, xv);

			return vector3(v);
		}
	};

	class vector4 final
	{
	public:
		float x, y, z, w;
	public:
		vector4() : x(0), y(0), z(0), w(0) {}
		vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		vector4(XMFLOAT4 v) : x(v.x), y(v.y), z(v.z), w(v.x) {}
	public:
		inline vector4 operator + (const vector3& v) const
		{
			return vector4(x + v.x, y + v.y, z + v.z, w);
		}
	public:
		XMVECTOR GetSIMD()
		{
			XMFLOAT4 v = XMFLOAT4(x, y, z, w);

			return XMLoadFloat4(&v);
		}
	public:
		inline static vector4 Convert(XMVECTOR xv)
		{
			XMFLOAT4 v;	XMStoreFloat4(&v, xv);

			return vector4(v);
		}
	};
}