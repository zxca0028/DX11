#pragma once

#include "Core.h"

namespace CLIENT
{
	class Pipeline final : public ISingleton
	{
	public:
		enum class STATE
		{
			VIEW,
			PROJ,
			ORTH
		};
	private:
		matrix mOrthoMatrix;
		matrix mViewMatrix;
		matrix mProjMatrix;
	public:
		virtual void Init() override;
	public:
		matrix GetMatrix(STATE state);
		void   SetMatrix(STATE state, const matrix matrix);
	};
}



