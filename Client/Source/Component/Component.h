#pragma once

#include "Core.h"

namespace CLIENT
{
	class Component abstract
	{
	public:
		struct COMPONENT_INIT_DESC
		{
			wstring path = L"";
			vector3 position;
		};
	protected:
		COMPONENT_INIT_DESC mInitDesc;
	public:
		virtual ~Component() = default;
	protected:
		virtual HRESULT Init(const COMPONENT_INIT_DESC* desc) = 0;
	};
}