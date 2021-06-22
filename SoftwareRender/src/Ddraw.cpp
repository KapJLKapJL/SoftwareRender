#include <algorithm>

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

bool DDraw::draw(Entity* entity)
{
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


	Triangle2D t{ {400.12539, 100.1351345}, {400.125154,500.12514}, {10., 10.} };

	
	static double angle;
	angle += 0.0275125;
	double angle_sin = sin(angle);
	double angle_cos = cos(angle);

	
	matrix<4, 4> to_world{ {1.,        0.,         0., 0.,
						    0., angle_cos, -angle_sin, 0.,
						    0., angle_sin,  angle_cos, 150.,
		                    0.,        0.,         0., 1.} };
	

	/*
	matrix<4, 4> to_world{ {1.,        0.,         0., 0.,
							0.,        1.,         0., 0.,
							0.,        0.,         1., 100.,
							0.,        0.,         0., 1.} };
	*/

	matrix<3, 4> projection{ {1., 0., 0., 0.,
		                      0., 1., 0., 0.,
		                      0., 0., 1., 0.} };

	//matrix<3, 3> viewport{ {} };

	while (!entity->eof())
	{
		auto f = entity->getFace();
		// Вершинный шейдер
		vector<4> v[3];
		for (int i = 0; i < 3; i++)
		{
			v[i] = { f.v[i].coord.x, f.v[i].coord.y, f.v[i].coord.z, 1. };
			v[i] = to_world * v[i];
		}

		if (isBackFace(v[0], v[1], v[2]))
			continue;

		// Пиксельный шейдер
		point2D p[3];
		for (int i = 0; i < 3; i++)
		{
			auto proj = projection * v[i];
			// viewport
			p[i].x = 400 + proj[0] * 200 / proj[2];
			p[i].y = 300 - proj[1] * 200 / proj[2];
		}

		t = { p[0], p[1], p[2] };
		//rasterize(t, srfc_desc, entity->getDiffuseMap());
		barRastrize({ p[0], p[1], p[2] }, srfc_desc);
	}

	if (FAILED(i_back_buffer->Unlock(NULL)))
		return false;

	// Флип
	if (FAILED(i_primary_surface->Flip(NULL, DDFLIP_WAIT))) {
		return false;
	}

	Sleep(55);

	return true;
}

bool DDraw::clear()
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
	return true;
}


void DDraw::rasterize(Triangle2D t, DDSURFACEDESC2 &desc, Texture* texture)
{
	// Сортировка по возрастанию Y (A<B<C)
	if (t.a.y > t.b.y) std::swap(t.a, t.b);
	if (t.a.y > t.c.y) std::swap(t.a, t.c);
	if (t.b.y > t.c.y) std::swap(t.b, t.c);

	// Коэффициент приращения Х относительно У для каждой каждой прямой
	double kCA = (t.c.x - t.a.x) / (t.c.y - t.a.y);
	double kBA = (t.b.x - t.a.x) / (t.b.y - t.a.y);
	double kCB = (t.c.x - t.b.x) / (t.c.y - t.b.y);

	// Лежит ли точка B правее прямой AC? (относительно зрителя)
	double xAC = kCA * (t.b.y - t.a.y) + t.a.x; // Тут была ошибка. Вспомнить откуда взялось это выражение!!!
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
	auto scanLine = [&](const int& y_top, const int& y_bot)
	{
		int x_l;
		int x_r;
		for (int y = y_top; y < y_bot; y++)
		{
			x_l = (int)x_left;
			x_r = (int)x_right;
			int y_mempitch = y * mempitch;
			for (int x = x_l; x < x_r; x++)
			{
				video_buffer[x + y_mempitch] = 0xFFFF0000;
			}
			x_left += k_left;
			x_right += k_right;
		}
	};

	// Закраска верхнего треугольника
	scanLine((int) t.a.y, (int)t.b.y);

	if (t.b.x > xAC)
	{
		k_left = kCA;
		k_right = kCB;
		x_left = x_left;
		x_right = t.b.x;
	}
	else
	{
		k_left = kCB;
		k_right = kCA;
		x_left = t.b.x;
		x_right = x_right;
	}

	// Закраска нижнего треугольника
	scanLine((int)t.b.y, (int)t.c.y);
}

void DDraw::barRastrize(matrix<3, 2> p, DDSURFACEDESC2& desc)
{      
	// (A<B<C) .y
	if (p[0][1] > p[1][1]) std::swap(p[0], p[1]);
	if (p[0][1] > p[2][1]) std::swap(p[0], p[2]);
	if (p[1][1] > p[2][1]) std::swap(p[1], p[2]);

	int top = p[0][1] > 0.01   ? (int)p[0][1] : 0;
	int bot = p[2][1] < 598.99 ? (int)p[2][1] : 599;
	if (top > bot)
		return;

	int left  = (int) min(p[0][0], min(p[1][0], p[2][0]));
	int right = (int) max(p[0][0], max(p[1][0], p[2][0]));

	left  = max(left, 0);
	right = min(right, 799);

	if (left > right)
		return;


	int mempitch = (int)(desc.lPitch >> 2);
	UINT* video_buffer = (UINT*)desc.lpSurface;
	UINT color = 0xFF + rand() % 0xFFFFFF;
	for (int y = top; y <= bot; y++)
	{
		int y_mempitch = y * mempitch;
		for (int x = left; x <= right; x++)
		{
			auto bar_screen = barycentric(p[0], p[1], p[2], { (double)x, (double)y });
			if (bar_screen.x < 0. || bar_screen.y < 0. || bar_screen.z < 0.)
				continue;
			video_buffer[x + y_mempitch] = color;
		}
	}
}
