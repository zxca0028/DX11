#pragma once

#include "Core.h"

namespace CLIENT
{
	class GameObject abstract
	{
	protected:
		virtual ~GameObject() = default;
	public:
		virtual void Init()   = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
	protected:
		virtual void UpdateObject() = 0;
		virtual void RenderObject() = 0;
	};
}