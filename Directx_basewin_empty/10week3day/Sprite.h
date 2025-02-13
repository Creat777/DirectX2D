#pragma once

#include <d2d1.h>
#include <Windows.h>
#include <wincodec.h>

#pragma comment(lib, "D2D1.lib")

#pragma comment(lib, "windowscodecs.lib")

#include "Graphics.h"


class Sprite
{
	Graphics* gfx;
	ID2D1Bitmap* bmp;

public :

	Sprite(wchar_t* filename, Graphics* gfx);
	~Sprite();
	void Draw();
};