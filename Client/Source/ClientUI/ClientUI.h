#pragma once

#include "Core.h"

namespace CLIENT
{
	class ClientUI final : public ISingleton
	{
	private:
		ImGuiIO* io;
	public:
		virtual void Init() override;
	public:
		void NewFrame();
		void EndFrame();
		void Shutdown();
	};
}