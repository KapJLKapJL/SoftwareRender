#ifndef FLAT_SHADER_H
#define FLAT_SHADER_H

#include "AbstractShader.h"

extern const ssr::point3D directional_light;
class ssr::Texture;

class FlatShader : public ssr::abstrctShader
{

public:
	virtual ~FlatShader() {};

	ssr::point3D vertex(const ssr::face& f, const int& idx) override
	{
		text_coord[0][idx] = f.v[idx].vt.x;
		text_coord[1][idx] = f.v[idx].vt.y;

		ssr::vector<4> v = { f.v[idx].coord.x, f.v[idx].coord.y, f.v[idx].coord.z, 1. };
		vert[idx] = projection * (to_world * v);
		if (idx == 2)
		{
			auto AB = vert[1] - vert[0];
			auto AC = vert[2] - vert[0];

			auto normal = ssr::cross({ AB[0], AB[1], AB[2] }, { AC[0], AC[1], AC[2] });
			intensity = ssr::dot(normal.normalize(), directional_light.normalize());
		}
		return vert[idx];
	};

	ssr::color pixel(const ssr::point3D& bar, ssr::Texture* t) override
	{
		ssr::color c;
		if (intensity < 0.)
		{
			c.ARGB = 0xFF000000;
		}
		else
		{
			auto uv = text_coord * bar;

			c = t->getPixel(uv.x, uv.y);
			c.B *= intensity;
			c.R *= intensity;
			c.G *= intensity;
		}

		return c;
	};

protected:
	ssr::matrix<2, 3> text_coord;
	ssr::matrix<3, 3> vert;
	double intensity{ 0. };
};

#endif // !FLAT_SHADER_H

