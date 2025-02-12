#include <Windows.h>
#include <d2d1.h>

#include "Graphics.h"

#pragma comment(lib, "D2D1.lib")

Graphics* graphics;

// canvas -> 2D
// sprite Lenderer -> 3D

// directX 2D <-> canvas

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //콜백 함수

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIns, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc; //모든 값을 0으로 초기화
	ZeroMemory(&wc, sizeof(WNDCLASS));
	wc.style = CS_HREDRAW | CS_VREDRAW; //비트 연산자
	wc.lpfnWndProc = WndProc; //프로시저 -> 콜백함수
	wc.hInstance = hInstance; //제어권
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; //윈도우 색 지정
	wc.lpszClassName = L"winclass"; //클래스 이름
	RegisterClass(&wc); //윈도우 형태를 등록

	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	//윈도우를 만든다.
	HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		L"winclass", L"기본 윈도우", WS_OVERLAPPEDWINDOW,
		100, 100, rect.right - rect.left, rect.bottom - rect.top,
		nullptr, nullptr, hInstance, nullptr);

	if (hWnd == false) return -1;

	graphics = new Graphics();

	if (graphics->Init(hWnd) == false)
	{
		delete graphics;
		return -1;
	}

	//윈도우를 보여준다.
	ShowWindow(hWnd, nCmdShow);
	
	//윈도우를 갱신한다.
	UpdateWindow(hWnd);

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		// PeekMessage <-> GetMessage
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) //메시지가 있는지만 검사
		{
			TranslateMessage(&msg); // 키보드 입력 변환
			DispatchMessage(&msg); // 메시지 처리 --> WndProc
		}
		else
		{
			graphics->BeginDraw();

			graphics->ClearScreen(0, 0, 1);

			graphics->EndDraw();
		}
	}

	delete graphics;

	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY: //이벤트
		PostQuitMessage(0); //-> 메시지 큐에 WM_QUIT가 들어간다.
		return 0;

	
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


