#include "..\hdr\Ddraw.h"

DDraw* DDraw::ddraw_instance = nullptr;

DDraw::DDraw() :i_ddraw(nullptr)
{
	if (!ddraw_instance)
		ddraw_instance = this;
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
	


	return true;
}
