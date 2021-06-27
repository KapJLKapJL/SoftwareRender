#ifndef PHONG_SHADER_H
#define PHONG_SHADER_H

#include <math.h>

#include "AbstractShader.h"


extern const point3D directional_light;

class PhongShader : public abstrctShader
{
public:
	virtual ~PhongShader() {};

	point3D vertex(const face& f, const int& idx) override
	{
		text_coord[0][idx] = f.v[idx].vt.x;
		text_coord[1][idx] = f.v[idx].vt.y;

		vector<4> n4 = { f.v[idx].vn.x, f.v[idx].vn.y, f.v[idx].vn.z, 0. };
		vector<3> n = projection * (to_world * n4);

		normals[0][idx] = n.x;
		normals[1][idx] = n.y;
		normals[2][idx] = n.z;

		vector<4> v = { f.v[idx].coord.x, f.v[idx].coord.y, f.v[idx].coord.z, 1. };
		return projection * (to_world * v);
	};

	color pixel(const point3D& bar, Texture* t) override
	{
		auto n = normals * bar;
		double diffuse = max(0., dot(n.normalize(), directional_light.normalize()) );

		color c;
		if (diffuse == 0.)
		{
			c.ARGB = 0xFF000000;
		}
		else
		{
			auto r = 2 * n * diffuse - directional_light;

			double specular = dot(r.normalize(), { 0.,0.,1. });

			double intensity = 0.9 * diffuse + 0.3 * pow(specular, 100.);

			//intensity = min(1., intensity);

			point2D uv = text_coord * bar;
			c = t->getPixel(uv.x, uv.y);
			c.R = min(255, intensity * c.R);
			c.G = min(255, intensity * c.G);
			c.B = min(255, intensity * c.B);
		}

		return c;
	};
protected:
	matrix<2, 3> text_coord;
	matrix<3, 3> normals;
};

#endif // !PHONG_SHADER_H

