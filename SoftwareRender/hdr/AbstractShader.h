#ifndef ABCTRCT_SHADER_H
#define ABSTRCT_SHADER_H

#include "MyMath.h"

class abstrctShader
{
public:
	virtual ~abstrctShader() {};

	void setWorldMatrix(const matrix<4, 4> &to_world_) { to_world = to_world_; };
	void setProjectionMatrix(const matrix<3, 4>& projection_) { projection = projection_; };

	virtual point3D vertex(const face &f, const int &idx) = 0;
	virtual color pixel(const point3D &bar, const color &col) = 0;

private:
	matrix<4, 4> to_world;
	matrix<3, 4> projection;
};

#endif // !ABCTRCT_SHADER_H

