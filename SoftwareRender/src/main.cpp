#include "../hdr/Ddraw.h"
#include "../hdr/Texture.h"
#include "../hdr/Mesh.h"
#include "../hdr/Entity.h"
#include "../hdr/MyMath.h"
#include <iostream>

int main() {
	Texture texture("banana\\textures\\Banana_BaseColor.png");

	
	Mesh mesh("banana\\source\\Banana.obj");
	Mesh cube("");

	Entity entity;
	entity.setMesh(&mesh);
	entity.setDiffuseMap(&texture);

	
	DDraw ddraw;

	if (!ddraw.create())
		return -1;

	while (ddraw.getWindow()->run())
	{
		if (ddraw.getWindow()->isExit())
			break;
		ddraw.clear();
		ddraw.draw(&entity);
	}
	

	return 0;
}