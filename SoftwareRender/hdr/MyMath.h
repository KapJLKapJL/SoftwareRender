#ifndef MY_MATH_H
#define MY_MATH_H

#include <cmath>

/////////////////////////////////////
#pragma pack(push, 1)
union color
{
	struct { unsigned char B, G, R, A; }; //(0 - A) (1 - R) (2 - G) (3 - B)
	unsigned int ARGB;
};
#pragma pack(pop)


struct triangle_indexes
{
	struct vertex_data { int ind, t_ind, n_ind; }; // Индексы
	vertex_data v[3]; // Вершины данного треугольника
};
//////////////////////////////////////


////////////  MATRIX  ///////////////

template<unsigned int n> struct vector
{
	vector() = default;
	double data[n]{};
	double& operator[](const unsigned int i)
	{
		if (i >= n) throw("Out of range!");
		return data[i];
	}
	double operator[] (const unsigned int i) const
	{
		if (i >= n) throw("Out of range!");
		return data[i];
	}
	double length() const
	{
		return std::sqrt(dot(*this, *this));
	}
	vector<n> normalize() const
	{
		return (*this) / length();
	}
};

template<unsigned int n> double dot(const vector<n> &v1, const vector<n> &v2)
{
	double dot_prdct = 0;
	for (int i = 0; i < n; i++)
		dot_prdct += v1[i] * v2[i];
	return dot_prdct;
}
vector<3> cross(const vector<3>& v1, const vector<3>& v2);

template<unsigned int n> vector<n> operator-(const vector<n>& v1, const vector<n>& v2)
{
	vector<n> ret;
	for (int i = 0; i < n; i++)
		ret[i] = v1[i] - v2[i];
	return ret;
}

template<unsigned int n> vector<n> operator/(const vector<n> &v, const double &d)
{
	vector<n> ret;
	for (int i = 0; i < n; i++)
		ret[i] = v[i] / d;
	return ret;
}


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


//////////// BASE TIPS ////////////

template<> struct vector<3>
{
	vector() = default;
	double x, y, z;
	double& operator[](const unsigned int i)
	{
		if (i >= 3) throw("Out of range!");
		return i == 0 ? x : (i == 1 ? y : z);
	}
	double operator[] (const unsigned int i) const
	{
		if (i >= 3) throw("Out of range!");
		return i == 0 ? x : (i == 1 ? y : z);
	}
	double length() const
	{
		return std::sqrt(dot(*this, *this));
	}
	vector<3> normalize() const
	{
		return (*this) / length();
	}
};
typedef vector<3> point3D;

template<> struct vector<2>
{
	vector() = default;
	double x, y;
	double& operator[](const unsigned int i)
	{
		if (i >= 2) throw("Out of range!");
		return i == 0 ? x : y;
	}
	double operator[] (const unsigned int i) const
	{
		if (i >= 2) throw("Out of range!");
		return i == 0 ? x : y;
	}
	double length() const
	{
		return std::sqrt(dot(*this, *this));
	}
	vector<2> normalize() const
	{
		return (*this) / length();
	}
};
typedef vector<2> point2D;

struct face
{
	struct vertex_data
	{
		point3D coord, vn;
		point2D vt;
	};
	vertex_data v[3];
};

struct Triangle2D
{
	point2D a, b, c;
};
///////////////////////////////////


//////////// FOR RENDER ////////////
bool isBackFace(const point3D& a, const point3D& b, const point3D& c);
point3D barycentric(const point2D &a, const point2D &b, const point2D& c, const point2D& p);
////////////////////////////////////

#endif // !MY_MATH_H

