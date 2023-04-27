#include "pch.h"
#include "Application.h"

using namespace CLIENT;

int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		UniquePtr<Application> app = CreateUniquePtr<Application>();

		if (app->Create())
		{
			app->Run();
		}

		app->Destroy();
	}
	catch (Exception& e)
	{
		LOG_ERROR(e.ToString());

		GlobalInstance::Release();
	}

}
