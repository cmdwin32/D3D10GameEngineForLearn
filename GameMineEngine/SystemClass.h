#include <Windows.h>
#include "InputClass.h"
#include "GraphicsClass.h"
#ifndef __SystemClass__
#define  __SystemClass__

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();
	bool Initialize();
	void Run();
	void Shutdown();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitialzieWindows(int&, int&);
	void ShutdonwWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

private:
	InputClass * m_Input;
	GraphicsClass * m_Graphics;
};

static SystemClass * ApplicationHandle = nullptr;

#endif