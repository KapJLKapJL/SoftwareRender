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


struct triangle_indexes
{
	struct vertex_data { int ind, t_ind, n_ind; }; // Индексы
	vertex_data v[3]; // Вершины данного треугольника
};


struct face
{
	struct vertex_data
	{ 
		point3D coord, vn;
		point2D vt;
	};
	vertex_data v[3];
};

#endif // !MY_MATH_H

