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
    bool result;
    
    // Create the Direct#d object
    m_D3D = new D3DClass;
    if (!m_D3D)
    {
        return false;
    }

    result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
        return false;
    }

    return true;
}

void GraphicsClass::ShutDown() {
    if (m_D3D)
    {
        m_D3D->ShutDown();
        delete m_D3D;
        m_D3D = nullptr;
    }
    return;
}

bool GraphicsClass::Frame() {
    bool result;

    result = Render();
    if (!result)
    {
        return false;
    }

    return true;
}

bool GraphicsClass::Render() {
    // Clear the buffer to begin the scene
    m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.f);

    // Present the rendered scewne to the screen
    m_D3D->EndScene();
    return true;
}
