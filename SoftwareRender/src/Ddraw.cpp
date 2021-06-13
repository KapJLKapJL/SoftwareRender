#include "..\hdr\Ddraw.h"

#include "..\hdr\MyMath.h"

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

bool DDraw::draw(Texture &texture)
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
			p = texture.getPixel(u, v);
			video_buffer[x + y * mempitch] = p.ARGB;
			v += dv;
		}
		u += du;
	}

	if (FAILED(i_back_buffer->Unlock(NULL)))
		return false;


	// ����
	if (FAILED(i_primary_surface->Flip(NULL, DDFLIP_WAIT))) {
		return false;
	}

	Sleep(50);

	return true;
}
