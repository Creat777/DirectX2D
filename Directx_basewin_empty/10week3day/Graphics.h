#pragma once

class Graphics
{
	// ��ġ������
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* rendertarget;

public :
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);
	ID2D1RenderTarget* GetRenderTarget();

	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
};