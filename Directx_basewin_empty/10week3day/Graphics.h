#pragma once

class Graphics
{
	// 장치포인터
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* rendertarget;

public :
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
};