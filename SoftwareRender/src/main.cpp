#include "../hdr/Ddraw.h"
#include "../hdr/Texture.h"
#include "../hdr/Mesh.h"
#include "../hdr/Entity.h"
#include "../hdr/MyMath.h"
#include <iostream>

int main() {
	//Texture texture("banana\\textures\\Banana_BaseColor.png");

	/*
	Mesh mesh("banana\\source\\Banana.obj");

	Entity entity;
	entity.setMesh(&mesh);

	face f;
	while (!entity.eof())
	{
		f = entity.getFace();
		int bgg = 1000;
	}
	*/

	matrix<2, 2> m1{ {1., 2., 3., 4.} };
	vector<2> v1{ 3., 0. };
	auto out1 = m1 * v1;
	matrix<2, 2> m2{ {3., 4., 0., 2.} };
	auto out2 = m1 * m2;
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