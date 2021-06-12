

#include "../hdr/Ddraw.h"

int main() {
	DDraw ddraw;

	if (!ddraw.create())
		return -1;

	while (ddraw.getWindow()->run())
	{
		if (ddraw.getWindow()->isExit())
			break;
	}

	return 0;
}