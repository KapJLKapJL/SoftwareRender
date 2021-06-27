#include <iostream>

#include "../hdr/Ddraw.h"
#include "../hdr/Texture.h"
#include "../hdr/Mesh.h"
#include "../hdr/Entity.h"
#include "../hdr/MyMath.h"
#include "../hdr/AbstractShader.h"
#include "../hdr/CubeMesh.h"
#include "../hdr/TextureShader.h"
#include "../hdr/FlatShader.h"
#include "../hdr/GouraudShader.h"
#include "../hdr/PhongShader.h"

const point3D directional_light{0.5, 0.3, -1};

int main() {
	Texture texture("banana\\textures\\Banana_BaseColor.png");
	
	Mesh mesh("banana\\source\\Banana.obj");
	CubeMesh cube;

	Entity entity;
	//entity.setMesh(&mesh);
	entity.setDiffuseMap(&texture);
	//entity.setPosition({0., 0., 100.});

	PhongShader shader;


	DDraw ddraw;

	if (!ddraw.create())
		return -1;

	double angleX = 0.;
	while (ddraw.isOpen())
	{
		if (ddraw.getWindow()->isExit())
			break;

		
		angleX += 0.0275125;

		entity.setRotation(angleX, 0., 0.);

		ddraw.clear();

		entity.setMesh(&mesh);
		entity.setPosition({ 50., 0., 100. });
		ddraw.draw(&entity, &shader);

		entity.setMesh(&cube);
		entity.setPosition({-3., -1., 5.});
		ddraw.draw(&entity, &shader);

		ddraw.display();
	}

	return 0;
}