#include "..\hdr\Mesh.h"

#include <iostream>
#include <sstream>

Mesh::Mesh(char const* filename)
{
	std::ifstream file(filename);

	if (!file)
		return;

	std::string s;
	while (!file.eof())
	{
		file >> s;

		if (s == "v")
			readVertexes(file);
		if (s == "vt")
			readTextureCoords(file);
		if (s == "vn")
			readNormals(file);
		if (s == "f")
			readFaceIndexes(file);
	}

	file.close();
}

Mesh::~Mesh()
{
}

void Mesh::readVertexes(std::ifstream& f)
{
	point3D v;
	f >> v.x >> v.y >> v.z;
	vertexes.push_back(v);
}

void Mesh::readTextureCoords(std::ifstream& f)
{
	point2D vt;
	f >> vt.u >> vt.v;
	texture_coords.push_back(vt);
}

void Mesh::readNormals(std::ifstream& f)
{
	point3D vn;
	f >> vn.x >> vn.y >> vn.z;
	normals.push_back(vn);
}

void Mesh::readFaceIndexes(std::ifstream& f)
{
	triangle_indexes t;
	std::string s;
	for (int i = 0; i < 3; i++)
	{
		f >> s;
		std::istringstream ss(s);
		char thrash;
		ss >> t.v[i].ind >> thrash >> t.v[i].n_ind >> thrash >> t.v[i].t_ind;
	}// Придумать защиту от нетреугольных поверхностей
	face_indexes.push_back(t);
}
