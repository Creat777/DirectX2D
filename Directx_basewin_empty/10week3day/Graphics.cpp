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
	// directX는 delete 대신 release를 사용
	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	// factory에 주소를 할당
	HRESULT res; // 결과가 올바른지 확인하는 변수

	// factory 획득
	res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	// rendertarget : 그래픽카드의 메모리 중에서 특정 영역, 텍스처를 입히는 부분
	// rendertarget 획득
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
