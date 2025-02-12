#include <Windows.h>
#include <d2d1.h>

#include "Graphics.h"

#pragma comment(lib, "D2D1.lib")

Graphics* graphics;

// canvas -> 2D
// sprite Lenderer -> 3D

// directX 2D <-> canvas

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //�ݹ� �Լ�

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIns, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc; //��� ���� 0���� �ʱ�ȭ
	ZeroMemory(&wc, sizeof(WNDCLASS));
	wc.style = CS_HREDRAW | CS_VREDRAW; //��Ʈ ������
	wc.lpfnWndProc = WndProc; //���ν��� -> �ݹ��Լ�
	wc.hInstance = hInstance; //�����
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; //������ �� ����
	wc.lpszClassName = L"winclass"; //Ŭ���� �̸�
	RegisterClass(&wc); //������ ���¸� ���

	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	//�����츦 �����.
	HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		L"winclass", L"�⺻ ������", WS_OVERLAPPEDWINDOW,
		100, 100, rect.right - rect.left, rect.bottom - rect.top,
		nullptr, nullptr, hInstance, nullptr);

	if (hWnd == false) return -1;

	graphics = new Graphics();

	if (graphics->Init(hWnd) == false)
	{
		delete graphics;
		return -1;
	}

	//�����츦 �����ش�.
	ShowWindow(hWnd, nCmdShow);
	
	//�����츦 �����Ѵ�.
	UpdateWindow(hWnd);

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		// PeekMessage <-> GetMessage
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) //�޽����� �ִ����� �˻�
		{
			TranslateMessage(&msg); // Ű���� �Է� ��ȯ
			DispatchMessage(&msg); // �޽��� ó�� --> WndProc
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
	case WM_DESTROY: //�̺�Ʈ
		PostQuitMessage(0); //-> �޽��� ť�� WM_QUIT�� ����.
		return 0;

	
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


