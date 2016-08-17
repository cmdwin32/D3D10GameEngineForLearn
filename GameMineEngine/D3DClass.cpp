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


D3DClass::~D3DClass()
{
}
