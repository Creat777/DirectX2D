#include <Windows.h>
#include <d2d1.h>

#include "Graphics.h"

Graphics::Graphics()
{
	factory = NULL;
	rendertarget = NULL;
}

Graphics::~Graphics()
{
	// directX�� delete ��� release�� ���
	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	// factory�� �ּҸ� �Ҵ�
	HRESULT res; // ����� �ùٸ��� Ȯ���ϴ� ����

	// factory ȹ��
	res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	// rendertarget : �׷���ī���� �޸� �߿��� Ư�� ����, �ؽ�ó�� ������ �κ�
	// rendertarget ȹ��
	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&rendertarget
	);
	
	if (res != S_OK) return false;

	return true;
	//return false;
}

void Graphics::ClearScreen(float r, float g, float b)
{
	rendertarget->Clear(
		D2D1::ColorF(r, g, b)
	);
}
