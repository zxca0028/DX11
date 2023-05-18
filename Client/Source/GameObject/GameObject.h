#pragma once

#include "Core.h"

namespace CLIENT
{
	class GameObject abstract
	{
	public:
		struct OBJECT_INIT_DESC
		{
			wstring texture;
			vector3 position;
		};
	protected:
		OBJECT_INIT_DESC mInitDesc;
	protected:
		virtual ~GameObject() = default;
	public:
		virtual HRESULT Init(const OBJECT_INIT_DESC& desc) = 0;
	public:
		virtual void Update() = 0;
		virtual void Render() = 0;
	protected:
		virtual void UpdateObject() = 0;
		virtual void RenderObject() = 0;
	};
}