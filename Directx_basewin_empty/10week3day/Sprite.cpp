#include "Sprite.h"



Sprite::Sprite(wchar_t* filename, Graphics* gfx)
{
	this->gfx = gfx;

	bmp = NULL;
	HRESULT result;

	result = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// windows Imaging Component
	IWICImagingFactory* wicFactory = NULL;

	result = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory
	);

	// ���ڴ����� ������ ���
	IWICBitmapDecoder* wicDecoder = NULL;
	result = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder	
	);
	IWICBitmapFrameDecode* wicFrame = NULL;
	result = wicDecoder->GetFrame(0, &wicFrame);

	// �����Ϳ��� bmp ���
	IWICFormatConverter* wicConverter = NULL;
	result = wicFactory->CreateFormatConverter(&wicConverter); // ������ ���
	// �������� ������ ������ �ʱ�ȭ
	result = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);

	result = gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&bmp
	);

	if (wicFactory)		wicFactory->Release();
	if (wicDecoder)		wicDecoder->Release();
	if (wicConverter)	wicConverter->Release();
	if (wicFrame)		wicFrame->Release();
}

Sprite::~Sprite()
{
	if (bmp) bmp->Release();
}

void Sprite::Draw()
{
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height)
	);
}
