#include "SystemClass.h"


SystemClass::SystemClass()
	:m_Input(nullptr)
	,m_Graphics(nullptr)
{

}

SystemClass::SystemClass(const SystemClass&) 
{

}


SystemClass::~SystemClass()
{

}

bool SystemClass::Initialize() {
	int screenWidth = 0;
	int screenHeight = 0;
	bool result = false;

	InitialzieWindows(screenWidth, screenHeight);

	m_Input = new InputClass();
	if (!m_Input) {
		return false;
	}
	m_Input->Initialize();

	m_Graphics = new GraphicsClass();
	if (!m_Graphics) {
		return false;
	}

	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if (!result)
	{
		return false;
	}

	return true;
}

void SystemClass::Run(){
	MSG msg ;
	bool done = nullptr;
	bool result = nullptr;
	
	::memset((void*)&msg, 0, sizeof(MSG));

	done = false;
	while (!done)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else {
			result = Frame();
			if (!result)
			{
				done = true;
			}
		}
	}
	return;
}

void SystemClass::Shutdown() {
	if (m_Graphics)
	{
		m_Graphics->ShutDown();
		delete m_Graphics;
		m_Graphics = nullptr;
	}

	if (m_Input)
	{
		delete m_Input;
		m_Input = nullptr;
	}

	ShutdonwWindows();

	return;
}

bool SystemClass::Frame() {
	bool result;

	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	result = m_Graphics->Frame();
	if (!result)
	{
		return false;
	}
	return true;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	switch (umsg)
	{
		case WM_KEYDOWN: {
			m_Input->KeyDown((unsigned int)wparam);
			return 0;
		}
		case WM_KEYUP: {
			m_Input->KeyUp((unsigned int)wparam);
			return 0;
		}
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	switch (umessage)
	{
	case WM_DESTROY:
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
}

void SystemClass::InitialzieWindows(int& screenWidth, int& screenHeight) {
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX = 0;
	int posY = 0;
	ApplicationHandle = this;

	m_hinstance = GetModuleHandle(NULL);

	m_applicationName = L"Engine";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (FULL_SCREEN) {
		::memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		posX = posY = 0;
	}
	else {
		screenWidth = 800;
		screenHeight = 600;

		posX = (int)((GetSystemMetrics(SM_CXSCREEN) - screenWidth) * 0.5);
		posY = (int)((GetSystemMetrics(SM_CYSCREEN) - screenHeight) * 0.5);
	}

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	ShowCursor(false);

	return;
}

void SystemClass::ShutdonwWindows() {
	ShowCursor(true);

	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(m_hwnd);
	m_hwnd = NULL;
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	ApplicationHandle = NULL;

	return;

}

