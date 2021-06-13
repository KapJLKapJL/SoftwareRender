#include "..\hdr\Ddraw.h"

#define INTRFC_RELEASE(intrfc) {if(intrfc){intrfc -> Release(); intrfc = nullptr;}}
#define CLEANING_STRUCT(ddstruct) {memset(&ddstruct, 0, sizeof(ddstruct)); ddstruct.dwSize = (sizeof(ddstruct)); }

DDraw* DDraw::ddraw_instance = nullptr;

DDraw::DDraw() :i_ddraw(nullptr), i_primary_surface(nullptr), i_back_buffer(nullptr)
{
	if (!ddraw_instance)
		ddraw_instance = this;
}

DDraw::~DDraw()
{
	INTRFC_RELEASE(i_back_buffer);
	INTRFC_RELEASE(i_primary_surface);
	INTRFC_RELEASE(i_ddraw);
	ddraw_instance = nullptr;
}

bool DDraw::create()
{
	if (!window.create())
		return false;

	HRESULT answer;
	
	answer = DirectDrawCreateEx(
		NULL,
		(void **) &i_ddraw,
		IID_IDirectDraw7,
		NULL
	);
	if (FAILED(answer)) {
		return false;
	}
	
	answer = i_ddraw->SetCooperativeLevel(
		window.getHWND(),
		DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX | DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT);
	//  Фулскрин         | Прочитать Ламота | Прочитать ламота| Разрешить ctrl+alt+del
	//														  | рисоваться наверху
	if (FAILED(answer)) {
		return false;
	}

	answer = i_ddraw->SetDisplayMode(
		800, 600, 32,
		0, 0);
	if (FAILED(answer)) {
		std::cout << "FAILED" << std::endl;
		return false;
	}

	DDSURFACEDESC2 desc;
	CLEANING_STRUCT(desc);
	desc.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	desc.dwBackBufferCount = 1;
	desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP;

	answer = i_ddraw->CreateSurface(&desc, &i_primary_surface, NULL);
	if (FAILED(answer)) {
		return false;
	}

	desc.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
	answer = i_primary_surface->GetAttachedSurface(&desc.ddsCaps, &i_back_buffer);
	if (FAILED(answer)) {
		return false;
	}

	return true;
}

bool DDraw::draw(Texture *texture)
{

	// Заливаю цветом
	DDBLTFX desc;
	CLEANING_STRUCT(desc);
	desc.dwFillColor = 0;

	if (FAILED(
		i_back_buffer->Blt(
			NULL, NULL, NULL,
			DDBLT_COLORFILL | DDBLT_WAIT,
			&desc)
	)) {
		return false;
	}

	// Рисую на поверхности
	DDSURFACEDESC2 srfc_desc;
	CLEANING_STRUCT(srfc_desc);
	if (FAILED(i_back_buffer->Lock(
		NULL,
		&srfc_desc,
		DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT,
		NULL)))
	{
		return false;
	}

	/*
	int mempitch = (int)(srfc_desc.lPitch >> 2);
	UINT* video_buffer = (UINT*)srfc_desc.lpSurface;

	double du = 1. / 400;
	double dv = 1. / 400;
	double u = 0., v = 0.;

	pixel_ARGB p;
	for (int x = 0; x < 400; x++)
	{
		for (int y = 0; y < 400; y++)
		{
			p = texture->getPixel(u, v);
			video_buffer[x + y * mempitch] = p.ARGB;
			v += dv;
		}
		u += du;
	}
	*/
	Triangle2D t{ {0, 0}, {0, 599}, {799, 300} };

	rasterize(t, srfc_desc, texture);
	//return false;

	if (FAILED(i_back_buffer->Unlock(NULL)))
		return false;


	// Флип
	if (FAILED(i_primary_surface->Flip(NULL, DDFLIP_WAIT))) {
		return false;
	}

	Sleep(50);

	return true;
}

void DDraw::rasterize(Triangle2D t, DDSURFACEDESC2 &desc, Texture* texture)
{
	// Сортировка по возрастанию Y (A<B<C)
	if (t.a.y > t.b.y) std::swap(t.a, t.b);
	if (t.a.y > t.c.y) std::swap(t.a, t.c);
	if (t.b.y > t.c.y) std::swap(t.b, t.c);

	// Коэффициент приращения Х относительно У для каждой каждой прямой
	double kCA = double(t.c.x - t.a.x) / (t.c.y - t.a.y);
	double kBA = double(t.b.x - t.a.x) / (t.b.y - t.a.y);
	double kCB = double(t.c.x - t.b.x) / (t.c.y - t.b.y);

	// Лежит ли точка B правее прямой AC? (относительно зрителя)
	double xAC = kCA * t.b.y + t.a.x;
	double k_left, k_right;
	if (t.b.x > xAC)
	{
		k_left = kCA;
		k_right = kBA;
	}
	else
	{
		k_left = kBA;
		k_right = kCA;
	}
	double x_left = t.a.x;
	double x_right = t.a.x;


	int mempitch = (int)(desc.lPitch >> 2);
	UINT* video_buffer = (UINT*)desc.lpSurface;
	// Закраска верхней части треугольника
	for (int y = t.a.y; y < t.b.y; y++)
	{
		for (int x = (int) x_left; x < x_right; x++)
		{
			video_buffer[x + y * mempitch] = 0xFFFF0000;
		}
		x_left += k_left;
		x_right += k_right;
	}

	if (t.b.x > xAC)
	{
		k_left = kCA;
		k_right = kCB;
	}
	else
	{
		k_left = kCB;
		k_right = kCA;
	}
	// Закраска нижней части треугольника
	for (int y = t.b.y; y < t.c.y; y++)
	{
		for (int x = (int)x_left; x < x_right; x++)
		{
			video_buffer[x + y * mempitch] = 0xFFFF0000;
		}
		x_left += k_left;
		x_right += k_right;
	}
}
