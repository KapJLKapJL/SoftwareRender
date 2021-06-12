#include "..\hdr\Ddraw.h"

DDraw* DDraw::ddraw_instance = nullptr;

DDraw::DDraw()
{
	if (!ddraw_instance)
		ddraw_instance = this;
}

bool DDraw::create()
{
	if (!window.create())
		return false;
	return true;
}
