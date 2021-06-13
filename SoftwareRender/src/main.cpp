

#include "../hdr/Ddraw.h"
#include "../hdr/Texture.h"

int main() {
	Texture texture("banana\\textures\\Banana_BaseColor.png");

	std::cout << texture.getHeigth() << std::endl;
	std::cout << texture.getWidth() << std::endl;
	std::cout << texture.getNumberChanels() << std::endl;

	pixel_ARGB p = texture.getPixel(0.9, 0.5);

	std::cout << p.ARGB << std::endl;

	/*
	DDraw ddraw;

	if (!ddraw.create())
		return -1;

	while (ddraw.getWindow()->run())
	{
		ddraw.draw();
		if (ddraw.getWindow()->isExit())
			break;
	}
	*/

	return 0;
}