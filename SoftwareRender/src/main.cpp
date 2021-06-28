#include <iostream>

#include "../hdr/Ddraw.h"
#include "../hdr/Texture.h"
#include "../hdr/Mesh.h"
#include "../hdr/Entity.h"
#include "../hdr/MyMath.h"
#include "../hdr/CubeMesh.h"
#include "../hdr/TextureShader.h"
#include "../hdr/FlatShader.h"
#include "../hdr/GouraudShader.h"
#include "../hdr/PhongShader.h"

const ssr::point3D directional_light{0.5, 0.3, -1};

int main() {
	ssr::Texture texture("banana\\textures\\Banana_BaseColor.png");
	ssr::Texture grid("banana\\textures\\grid_2.jpg");
	
	ssr::Mesh mesh("banana\\source\\Banana.obj");
	ssr::CubeMesh cube;

	ssr::Entity entity;

	PhongShader shader;

	ssr::DDraw ddraw;

	double angleY = 0.79;
	double angleX = -0.52;

	if (!ddraw.create())
		return -1;
	while (ddraw.isOpen())
	{
		if (ddraw.isExit())
			break;

		ddraw.clear();

		entity.setMesh(&mesh);
		entity.setDiffuseMap(&texture);
		entity.setPosition({ 2.5, 0., 5. });
		entity.setRotation(0., 3.14, 0.26);
		entity.setMaxRadius(3.);
		ddraw.draw(&entity, &shader);
		
		entity.setMesh(&cube);
		entity.setDiffuseMap(&grid);
		entity.setPosition({-1.5, 0., 5.});
		entity.setRotation(angleX, 0.2, 0.);
		entity.setMaxRadius(3.);
		ddraw.draw(&entity, &shader);

		ddraw.display();
	}

	return 0;
}