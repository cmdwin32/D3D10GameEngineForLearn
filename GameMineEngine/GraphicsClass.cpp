#include "GraphicsClass.h"



GraphicsClass::GraphicsClass()
	:m_D3D(nullptr)
{
}

GraphicsClass::GraphicsClass(const GraphicsClass&) {

}


GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd) {
	return true;
}

void GraphicsClass::ShutDown() {
	return;
}

bool GraphicsClass::Frame() {
	return true;
}

bool GraphicsClass::Render() {
	return true;
}
