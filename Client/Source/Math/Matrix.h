#pragma once

#include "Math/Vector.h"

namespace CLIENT
{
	class matrix final
	{
	public:
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;
	public:
		matrix()
			: _11(1.0f), _12(0.0f), _13(0.0f), _14(0.0f),
			  _21(0.0f), _22(1.0f), _23(0.0f), _24(0.0f),
			  _31(0.0f), _32(0.0f), _33(1.0f), _34(0.0f),
			  _41(0.0f), _42(0.0f), _43(0.0f), _44(1.0f)
		{}
		matrix
		(
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44
		)
			: _11(_11), _12(_12), _13(_13), _14(_14),
			  _21(_21), _22(_22), _23(_23), _24(_24),
			  _31(_31), _32(_32), _33(_33), _34(_34),
			  _41(_41), _42(_42), _43(_43), _44(_44)
		{}
		matrix(XMFLOAT4X4 m)
			: _11(m._11), _12(m._12), _13(m._13), _14(m._14),
			  _21(m._21), _22(m._22), _23(m._23), _24(m._24),
			  _31(m._31), _32(m._32), _33(m._33), _34(m._34),
			  _41(m._41), _42(m._42), _43(m._43), _44(m._44)
		{}
	public:
		XMMATRIX GetSIMD()
		{
			XMFLOAT4X4 m = XMFLOAT4X4(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44);

			return XMLoadFloat4x4(&m);
		}
	public:
		inline static matrix Convert(XMMATRIX xm)
		{
			XMFLOAT4X4 m;

			XMStoreFloat4x4(&m, xm);

			return matrix(m);
		}
	};
}