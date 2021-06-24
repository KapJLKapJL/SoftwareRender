#include <iostream>

#include "../hdr/Ddraw.h"
#include "../hdr/Texture.h"
#include "../hdr/Mesh.h"
#include "../hdr/Entity.h"
#include "../hdr/MyMath.h"
#include "../hdr/AbstractShader.h"
#include "../hdr/CubeMesh.h"


class MicroShader : public abstrctShader
{
public:
	virtual ~MicroShader() {};

	point3D vertex(const face& f, const int& idx) override
	{
		text_coord[0][idx] = f.v[idx].vt.x;
		text_coord[1][idx] = f.v[idx].vt.y;

		vector<4> v = { f.v[idx].coord.x, f.v[idx].coord.y, f.v[idx].coord.z, 1. };
		return projection * (to_world * v);
	};

	color pixel(const point3D& bar, Texture *t) override
	{
		point2D uv = text_coord * bar;
		return t->getPixel(uv.x, uv.y);
	};
private:
	matrix<2, 3> text_coord;
};



int main() {
	Texture texture("banana\\textures\\Banana_BaseColor.png");
	
	Mesh mesh("banana\\source\\Banana.obj");
	CubeMesh cube;

	Entity entity;
	entity.setMesh(&mesh);
	entity.setDiffuseMap(&texture);
	entity.setPosition({0., 0., 100.});

	MicroShader shader;

	DDraw ddraw;

	if (!ddraw.create())
		return -1;

	double angleX = 0.;
	while (ddraw.getWindow()->run())
	{
		if (ddraw.getWindow()->isExit())
			break;

		angleX += 0.0275125;

		entity.setRotationX(angleX);

		ddraw.clear();
		ddraw.draw(&entity, &shader);
	}

	return 0;
}