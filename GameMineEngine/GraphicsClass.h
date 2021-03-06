#include "D3DClass.h"
#ifndef __GRAPHICESCLASS__
#define  __GraphicsClass__
#include <windows.h>
// GLOBALS //
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int,int,HWND);
	void ShutDown();
	bool Frame();

private:
	bool Render();
private:
	D3DClass* m_D3D;
};

#endif // !


