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
	//  ��������         | ��������� ������ | ��������� ������| ��������� ctrl+alt+del
	//														  | ���������� �������
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

bool DDraw::draw(Entity* entity, abstrctShader* shader)
{
	shader->setWorldMatrix(entity->getModelMatrix());

	matrix<3, 4> projection{ {1., 0., 0., 0.,
							  0., 1., 0., 0.,
							  0., 0., 1., 0.} };

	shader->setProjectionMatrix(projection);

	// ����� �� �����������
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

	//matrix<3, 3> viewport{ {} };

	while (!entity->eof())
	{
		auto f = entity->getFace();

		point3D v[3];
		for (int i = 0; i < 3; i++)
		{
			v[i] = shader->vertex(f, i);
		}

		if (isBackFace(v[0], v[1], v[2]))
			continue;

		matrix<3, 2> p;
		for (int i = 0; i < 3; i++)
		{
			p[i].x = 400 + v[i].x * 200 / v[i].z;
			p[i].y = 300 - v[i].y * 200 / v[i].z;
		}

		barRastrize(p, entity->getDiffuseMap(), srfc_desc, shader);
		//rasterize(p, entity->getDiffuseMap(), srfc_desc, shader);
	}

	if (FAILED(i_back_buffer->Unlock(NULL)))
		return false;

	Sleep(55);

	return true;
}

bool DDraw::clear()
{
	// ������� ������
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

bool DDraw::display()
{
	if (FAILED(i_primary_surface->Flip(NULL, DDFLIP_WAIT))) {
		return false;
	}

	return true;
}


void DDraw::rasterize(matrix<3, 2> &p, Texture* texture, const DDSURFACEDESC2& desc, abstrctShader* shader)
{
	// ���������� �� ����������� Y (A<B<C)
	if (p[0][1] > p[1][1]) std::swap(p[0], p[1]);
	if (p[0][1] > p[2][1]) std::swap(p[0], p[2]);
	if (p[1][1] > p[2][1]) std::swap(p[1], p[2]);

	// ����������� ���������� � ������������ � ��� ������ ������ ������
	double kCA = (p[2][0] - p[0][0]) / (p[2][1] - p[0][1]);
	double kBA = (p[1][0] - p[0][0]) / (p[1][1] - p[0][1]);
	double kCB = (p[2][0] - p[1][0]) / (p[2][1] - p[1][1]);

	// ����� �� ����� B ������ ������ AC? (������������ �������)
	double xAC = kCA * (p[1][1] - p[0][1]) + p[0][0]; // ��� ���� ������. ��������� ������ ������� ��� ���������!!!
	double k_left, k_right;
	if (p[1][0] > xAC)
	{
		k_left = kCA;
		k_right = kBA;
	}
	else
	{
		k_left = kBA;
		k_right = kCA;
	}
	double x_left = p[0][0];
	double x_right = p[0][0];


	int mempitch = (int)(desc.lPitch >> 2);
	UINT* video_buffer = (UINT*)desc.lpSurface;
	auto scanLine = [&](const int& y_top, const int& y_bot)
	{
		int x_l;
		int x_r;
		for (int y = y_top; y <= y_bot; y++)
		{
			x_l = (int)x_left;
			x_r = (int)x_right;
			int y_mempitch = y * mempitch;
			for (int x = x_l; x <= x_r; x++)
			{
				auto bar_screen = barycentric(p[0], p[1], p[2], { (double)x, (double)y });
				if (bar_screen.x < 0. || bar_screen.y < 0. || bar_screen.z < 0.)
					continue;
				video_buffer[x + y_mempitch] = shader->pixel(bar_screen, texture).ARGB;
			}
			x_left += k_left;
			x_right += k_right;
		}
	};

	// �������� �������� ������������
	scanLine((int)p[0][1], (int)p[1][1]);

	if (p[1][0] > xAC)
	{
		k_left = kCA;
		k_right = kCB;
		x_left = x_left;
		x_right = p[1][0];
	}
	else
	{
		k_left = kCB;
		k_right = kCA;
		x_left = p[1][0];
		x_right = x_right;
	}

	// �������� ������� ������������
	scanLine((int)p[1][1], (int)p[2][1]);
}

void DDraw::barRastrize(const matrix<3, 2> &p, Texture* texture, const DDSURFACEDESC2& desc, abstrctShader *shader)
{      
	// (A<B<C) .y
	/*
	if (p[0][1] > p[1][1]) std::swap(p[0], p[1]);
	if (p[0][1] > p[2][1]) std::swap(p[0], p[2]);
	if (p[1][1] > p[2][1]) std::swap(p[1], p[2]);
	*/

	int top = (int) min(p[0][1], min(p[1][1], p[2][1]));;
	int bot = (int) max(p[0][1], max(p[1][1], p[2][1]));;

	top = max(top, 0);
	bot = min(bot, 599);
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
	for (int y = top; y <= bot; y++)
	{
		int y_mempitch = y * mempitch;
		for (int x = left; x <= right; x++)
		{
			auto bar_screen = barycentric(p[0], p[1], p[2], { (double)x, (double)y });
			if (bar_screen.x < 0. || bar_screen.y < 0. || bar_screen.z < 0.)
				continue;
			video_buffer[x + y_mempitch] = shader->pixel(bar_screen, texture).ARGB; // ����
		}
	}
}
