

#include "../hdr/Window.h"

int main() {
	Window window;

	if (!window.create())
		return -1;

	while (window.run())
	{
		if (window.isExit())
			break;
	}

	return 0;
}