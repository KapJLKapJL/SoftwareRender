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

		s = "";
	}
	file.close();

	faces_vector_size = face_indexes.size();
}

Mesh::~Mesh()
{
}

face Mesh::getFace(unsigned int face_number)
{
	triangle_indexes ti = face_indexes.at(face_number);

	face f;
	for (int i = 0; i < 3; i++)
	{
		f.v[i].coord = vertexes.at(ti.v[i].ind);
		f.v[i].vn = normals.at(ti.v[i].n_ind);
		f.v[i].vt = texture_coords.at(ti.v[i].t_ind);
	}
	return f;
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
		int ind, n_ind, t_ind;
		ss >> ind >> thrash >> t_ind >> thrash >> n_ind;
		t.v[i].ind = --ind;
		t.v[i].n_ind = --n_ind;
		t.v[i].t_ind = --t_ind;
	}// Придумать защиту от нетреугольных поверхностей
	face_indexes.push_back(t);
	
}
