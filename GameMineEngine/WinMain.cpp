#include "SystemClass.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	SystemClass * SysCls = nullptr;
	bool result = false;

	SysCls = new SystemClass();
	
	if (!SysCls) {
		return 0;
	}
	
	result = SysCls->Initialize();
	if (result)
	{
		SysCls->Run();
	}
	
	SysCls->Shutdown();
	delete SysCls;
	SysCls = nullptr;


	return 0;
}