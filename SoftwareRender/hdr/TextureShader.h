#ifndef TEXTURE_SHADER_H
#define TEXTURE_SHADER_H

#include "AbstractShader.h"
#include "Texture.h"

class TextureShader : public abstrctShader
{
public:
	virtual ~TextureShader() {};

	point3D vertex(const face& f, const int& idx) override
	{
		text_coord[0][idx] = f.v[idx].vt.x;
		text_coord[1][idx] = f.v[idx].vt.y;

		vector<4> v = { f.v[idx].coord.x, f.v[idx].coord.y, f.v[idx].coord.z, 1. };
		return projection * (to_world * v);
	};

	color pixel(const point3D& bar, Texture* t) override
	{
		point2D uv = text_coord * bar;
		return t->getPixel(uv.x, uv.y);
	};
protected:
	matrix<2, 3> text_coord;
};

#endif // !TEXTURE_SHADER_H

