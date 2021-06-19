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
		if (i >= n) throw("Out of range!");
		return data[i];
	}
	float operator[] (const unsigned int i) const
	{
		if (i >= n) throw("Out of range!");
		return data[i];
	}
};

template<unsigned int n> float dot(const vector<n> &v1, const vector<n> &v2)
{
	float dot_prdct = 0;
	for (int i = 0; i < n; i++)
		dot_prdct += v1[i] * v2[i];
	return dot_prdct;
}


vector<3> cross(const vector<3>& v1, const vector<3>& v2);


template<unsigned int nrows, unsigned int ncols> struct matrix
{
	matrix() = default;
	vector<ncols> rows[nrows]{ {} };
	vector<ncols>& operator[](const unsigned int i)
	{
		if (i >= nrows) throw("Out of range!");
		return rows[i];
	}
	const vector<ncols>& operator[](const unsigned int i) const
	{
		if (i >= nrows) throw("Out of range!");
		return rows[i];
	}

	vector<nrows> getCol(const unsigned int i) const
	{
		if(i >= ncols) throw("Out of range!");
		vector<nrows> ret;
		for (int col = 0; col < nrows; col++)
			ret[col] = rows[col][i];
		return ret;
	}
};

template<unsigned int nrows, unsigned int ncols> vector<nrows> operator*(const matrix<nrows, ncols>& m, const vector<ncols>& v)
{
	vector<nrows> ret;

	for (int i = 0; i < nrows; i++)
		ret[i] = dot(m[i], v);

	return ret;
}

template<unsigned int nrows_l, unsigned int ncols_l, unsigned int ncols_r> matrix<ncols_r, nrows_l> operator*(const matrix<nrows_l, ncols_l>& m_l, const matrix<ncols_l, ncols_r>& m_r)
{
	matrix<ncols_r, nrows_l> ret;

	for (int i = 0; i < ncols_r; i++)
		for (int j = 0; j < nrows_l; j++)
			ret[i][j] = dot(m_l[j], m_r.getCol(i));

	return ret;
}

///////////////////////////////////////

#endif // !MY_MATH_H

