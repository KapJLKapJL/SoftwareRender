#include "../hdr/MyMath.h"

vector<3> cross(const vector<3>& v1, const vector<3>& v2)
{
	vector<3> ret;
	ret[0] = v1[1] * v2[2] - v1[2] * v2[1];
	ret[1] = v1[2] * v2[0] - v1[0] * v2[2];
	ret[2] = v1[0] * v2[1] - v1[1] * v2[0];
	return ret;
}