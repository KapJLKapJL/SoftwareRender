#include "..\hdr\Ddraw.h"

#define INTRFC_RELEASE(intrfc) {if(intrfc){intrfc -> Release(); intrfc = nullptr;}}

DDraw* DDraw::ddraw_instance = nullptr;

DDraw::DDraw() :i_ddraw(nullptr)
{
	if (!ddraw_instance)
		ddraw_instance = this;
}

DDraw::~DDraw()
{
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
		std::cout << "FAILED" << std::endl;
		return false;
	}

	return true;
}
