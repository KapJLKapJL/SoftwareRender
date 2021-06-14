#ifndef MY_MATH_H
#define MY_MATH_H

#pragma pack(push, 1)
union pixel_ARGB
{
	struct { unsigned char B, G, R, A; }; //(0 - A) (1 - R) (2 - G) (3 - B)
	unsigned int ARGB;
};
#pragma pack(pop)

union point2D
{
	struct { int	x, y; };
	struct { float	u, v; };
};

struct point3D
{
	double x, y, z;
};

struct Triangle2D
{
	point2D a, b, c;
};

/*
struct Triangle
{
	point3D  *v0,  *v1,  *v2;
	point2D *vt0, *vt1, *vt2;
	point3D *vn0, *vn1, *vn2;
};
*/

#endif // !MY_MATH_H

