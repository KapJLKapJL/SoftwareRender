#include <algorithm>

#include "..\hdr\Ddraw.h"
#include "..\hdr\AbstractShader.h"
#include "..\hdr\Entity.h"


#define INTRFC_RELEASE(intrfc) {if(intrfc){intrfc -> Release(); intrfc = nullptr;}}
#define CLEANING_STRUCT(ddstruct) {memset(&ddstruct, 0, sizeof(ddstruct)); ddstruct.dwSize = (sizeof(ddstruct)); }


namespace ssr
{

	DDraw* DDraw::ddraw_instance = nullptr;

	DDraw::DDraw()
	{
		if (!ddraw_instance)
			ddraw_instance = this;
	}

	DDraw::~DDraw()
	{
		ddraw_instance = nullptr;
	}

	bool DDraw::create()
	{
		if (!window.create())
			return false;

		HRESULT answer;

		answer = DirectDrawCreateEx(
			NULL,
			(void**)&i_ddraw,
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
		// In video memory surfaces
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

		// In system memory surfaces
		video_buffer = std::make_unique<unsigned int[]>(800 * 600);
		CLEANING_STRUCT(desc);
		desc.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_LPSURFACE | DDSD_PITCH;
		desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
		desc.dwWidth = 800;
		desc.dwHeight = 600;
		desc.lpSurface = video_buffer.get();
		desc.lPitch = 800 * 4;

		answer = i_ddraw->CreateSurface(&desc, &i_video_buffer, NULL);
		if (FAILED(answer)) {
			std::cout << "++++++++++++" << std::endl;
			return false;
		}

		z_buffer = std::make_unique<double[]>(800 * 600);

		return true;
	}

	bool DDraw::draw(Entity* entity, abstrctShader* shader)
	{
		shader->setWorldMatrix(entity->getModelMatrix());

		matrix<3, 4> projection{ {1., 0., 0., 0.,
								  0., 1., 0., 0.,
								  0., 0., 1., 0.} };

		shader->setProjectionMatrix(projection);

		while (!entity->eof())
		{
			auto f = entity->getFace();

			matrix<3, 3> v;
			for (int i = 0; i < 3; i++)
			{
				v[i] = shader->vertex(f, i);
			}

			if (isBackFace(v[0], v[1], v[2]))
				continue;

			barRastrize(v, entity->getDiffuseMap(), shader);
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
			i_video_buffer->Blt(
				NULL, NULL, NULL,
				DDBLT_COLORFILL | DDBLT_WAIT,
				&desc)
		))
		{
			return false;
		}
		
		ZeroMemory(z_buffer.get(), 800 * 600 * 8);

		return true;
	}

	bool DDraw::display()
	{
		HRESULT answer;

		answer = i_back_buffer->BltFast(0,0, i_video_buffer.Get(), 0, DDBLTFAST_WAIT);
		if (FAILED(answer)) {
			return false;
		}

		if (FAILED(i_primary_surface->Flip(NULL, DDFLIP_WAIT))) {
			return false;
		}

		return true;
	}

	void DDraw::barRastrize(const matrix<3, 3>& v, Texture* texture, abstrctShader* shader)
	{
		matrix<3, 2> p;
		for (int i = 0; i < 3; i++)
		{
			p[i].x = 400 + v[i].x * 267 / v[i].z;
			p[i].y = 300 - v[i].y * 267 / v[i].z;
		}

		int top = (int)min(p[0][1], min(p[1][1], p[2][1]));;
		int bot = (int)max(p[0][1], max(p[1][1], p[2][1]));;

		top = max(top, 0);
		bot = min(bot, 599);
		if (top > bot)
			return;

		int left = (int)min(p[0][0], min(p[1][0], p[2][0]));
		int right = (int)max(p[0][0], max(p[1][0], p[2][0]));

		left = max(left, 0);
		right = min(right, 799);
		if (left > right)
			return;


		auto AB = p[1] - p[0];
		auto AC = p[2] - p[0];
		double k_min = AB.x * AC.y - AC.x * AB.y;


		for (int y = top; y <= bot; y++)
		{
			//int y_mempitch = y * mempitch;
			int y_800 = y * 800;


			double PAy = p[0].y - (double)y;
			double ABxPAy = AB.x * PAy;
			double ACxPAy = AC.x * PAy;


			for (int x = left; x <= right; x++)
			{
				double PAx = p[0].x - (double)x;
				double i_min = ACxPAy - PAx * AC.y;
				double j_min = PAx * AB.y - ABxPAy;

				point2D uv{ i_min / k_min, j_min / k_min };

				point3D bar_screen{ 1. - uv.x - uv.y, uv.x, uv.y };

				if (bar_screen.x < 0. || bar_screen.y < 0. || bar_screen.z < 0.)
					continue;

				point3D bar_3D{ bar_screen.x / v[0].z, bar_screen.y / v[1].z, bar_screen.z / v[2].z };
				bar_3D = bar_3D / (bar_3D.x + bar_3D.y + bar_3D.z);

				double z = 1. / dot({ v[0].z, v[1].z, v[2].z }, bar_3D);

				if (z_buffer[x + y_800] > z)
					continue;

				video_buffer[x + y_800] = shader->pixel(bar_3D, texture).ARGB; // Ужас
				z_buffer[x + y_800] = z;
			}
		}
	}// BarRasterize

}//namespace ssr
