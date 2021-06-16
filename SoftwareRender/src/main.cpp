//#include "../hdr/Ddraw.h"
//#include "../hdr/Texture.h"
#include "../hdr/Mesh.h"

int main() {
	//Texture texture("banana\\textures\\Banana_BaseColor.png");


	Mesh mesh("banana\\source\\Banana.obj");

	/*
	DDraw ddraw;

	if (!ddraw.create())
		return -1;

	while (ddraw.getWindow()->run())
	{
		ddraw.draw(&texture);
		if (ddraw.getWindow()->isExit())
			break;
	}
	*/
	
	return 0;
}