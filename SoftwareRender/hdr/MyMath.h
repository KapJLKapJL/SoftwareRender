#ifndef MY_MATH_H
#define MY_MATH_H

/////////////////////////////////////
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



////////////  MATRIX  ///////////////

template<unsigned int n> struct vector
{
	vector() = default;
	float data[n]{};
	float& operator[](const unsigned int i)
	{
		if (i >= n) throw(-1);
		return data[i];
	}
	float operator[] (const unsigned int i) const
	{
		if (i >= n) throw(-1);
		return data[i];
	}
};

template<unsigned int n> float dot(vector<n> &v1, vector<n> &v2)
{
	float dot_prdct = 0;
	for (int i = 0; i < n; i++)
		dot_prdct += v1[i] * v2[i];
	return dot_prdct;
}

///////////////////////////////////////

#endif // !MY_MATH_H

