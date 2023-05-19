#include "pch.h"
#include "Pipeline.h"

namespace CLIENT
{
	void CLIENT::Pipeline::Init()
	{
	}

	matrix Pipeline::GetMatrix(STATE state)
	{
		switch (state)
		{
		case STATE::VIEW:
			return mViewMatrix;
			
		case STATE::PROJ:
			return mProjMatrix;

		case STATE::ORTH:
			return mOrthoMatrix;
		}
	}

	void Pipeline::SetMatrix(STATE state, const matrix& matrix)
	{
		switch (state)
		{
		case STATE::VIEW:
			mViewMatrix = matrix;

		case STATE::PROJ:
			mProjMatrix = matrix;

		case STATE::ORTH:
			mOrthoMatrix = matrix;
		}
	}
}