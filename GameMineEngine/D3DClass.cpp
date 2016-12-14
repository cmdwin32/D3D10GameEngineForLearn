#include "D3DClass.h"



D3DClass::D3DClass()
	:m_device(nullptr)
	,m_swapChain(nullptr)
	,m_renderTargetView(nullptr)
	,m_depthStencilBuffer(nullptr)
	,m_depthStencilState(nullptr)
	,m_depthStencilView(nullptr)
	,m_rasterState(nullptr)
{
}

D3DClass::D3DClass(const D3DClass&) {

}


D3DClass::~D3DClass()
{

}

bool D3DClass::Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullScreen, float screenDepth, float screenNear) {
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes = 0;
	unsigned int i = 0;
	unsigned int numerator = 0;
	unsigned int denominator = 0;
	unsigned int stringLength;
	DXGI_MODE_DESC* displayModelList;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D10_TEXTURE2D_DESC depthBufferDesc;
	D3D10_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D10_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D10_VIEWPORT viewport;
	float fieldOfView;
	float screenAspect;
	D3D10_RASTERIZER_DESC rasterDesc;

	m_vsync_enabled = vsync;

    // Create a DirectX graohics interface factory
    result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
    if (FAILED(result))
    {
        return false;
    }

    result = factory->EnumAdapters(0, &adapter);
    if (FAILED(result))
    {
        return false;
    }
    
    // Ebynerate the orimary adapter output(monitor)
    result = adapter->EnumOutputs(0, &adapterOutput);
    if (FAILED(result))
    {
        return false;
    }

    // Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output(monitor)
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,DXGI_ENUM_MODES_INTERLACED,&numModes,NULL);
    if (FAILED(result))
    {
        return false;
    }

    // Create a list to hold all the possible display modes for the monitor/video card combination
    displayModelList = new DXGI_MODE_DESC[numModes];
    if (!displayModelList)
    {
        return false;
    }

    // Now fill the display mode list structures
    result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModelList);
    if (FAILED(result))
    {
        return false;
    }

    // now go through all the display modes and find the one that matches the screen width and height
    // When a match is found store the numerator and denominator of the refresh rate for that monitor
    for (i = 0; i < numModes; i++)
    {
        if (
            displayModelList[i].Width == (unsigned int)screenWidth
            &&
            displayModelList[i].Height == (unsigned int)screenHeight
            )
        {
            numerator = displayModelList[i].RefreshRate.Numerator;
            denominator = displayModelList[i].RefreshRate.Denominator;
        }
    }

}   


