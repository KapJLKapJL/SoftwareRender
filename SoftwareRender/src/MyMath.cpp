#include "../hdr/MyMath.h"


namespace ssr
{

	vector<3> cross(const vector<3>& v1, const vector<3>& v2)
	{
		vector<3> ret;
		ret[0] = v1[1] * v2[2] - v1[2] * v2[1];
		ret[1] = v1[2] * v2[0] - v1[0] * v2[2];
		ret[2] = v1[0] * v2[1] - v1[1] * v2[0];
		return ret;
	}

	bool isBackFace(const point3D& a, const point3D& b, const point3D& c)
	{
		auto AB = b - a;
		auto AC = c - a;

		auto normal = cross({ AB[0], AB[1], AB[2] }, { AC[0], AC[1], AC[2] });
		auto scalar = dot(normal, { a[0], a[1], a[2] });

		return scalar > 0.;
	}

	point3D barycentric(const point2D& a, const point2D& b, const point2D& c, const point2D& p)
	{
		point3D uv = cross({ b.x - a.x, c.x - a.x, a.x - p.x }, { b.y - a.y, c.y - a.y, a.y - p.y });

		double u = uv.x / uv.z;
		double v = uv.y / uv.z;

		return { 1. - u - v, u, v };
	}
}//namespace ssr
