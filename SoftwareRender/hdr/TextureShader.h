#ifndef TEXTURE_SHADER_H
#define TEXTURE_SHADER_H

#include "AbstractShader.h"

class ssr::Texture;

class TextureShader : public ssr::abstrctShader
{
public:
	virtual ~TextureShader() {};

	ssr::point3D vertex(const ssr::face& f, const int& idx) override
	{
		text_coord[0][idx] = f.v[idx].vt.x;
		text_coord[1][idx] = f.v[idx].vt.y;

		ssr::vector<4> v = { f.v[idx].coord.x, f.v[idx].coord.y, f.v[idx].coord.z, 1. };
		return projection * (to_world * v);
	};

	ssr::color pixel(const ssr::point3D& bar, ssr::Texture* t) override
	{
		ssr::point2D uv = text_coord * bar;
		return t->getPixel(uv.x, uv.y);
	};
protected:
	ssr::matrix<2, 3> text_coord;
};

#endif // !TEXTURE_SHADER_H

