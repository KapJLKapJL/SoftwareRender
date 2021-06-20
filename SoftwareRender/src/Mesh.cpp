#include "..\hdr\Mesh.h"

#include <iostream>
#include <sstream>

Mesh::Mesh(char const* filename)
{
	std::ifstream file(filename);

	if (!file)
	{
		makeCube();
	}
	else
	{
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

void Mesh::makeCube()
{
	// Vertexes of cube
	point3D v;
	v = { 1, 1, 1 };
	vertexes.push_back(v);
	v = { -1, 1, 1 };
	vertexes.push_back(v);
	v = { -1, -1, 1 };
	vertexes.push_back(v);
	v = { 1, -1, 1 };
	vertexes.push_back(v);
	v = { 1, 1, -1 };
	vertexes.push_back(v);
	v = { -1, 1, -1 };
	vertexes.push_back(v);
	v = { -1, -1, -1 };
	vertexes.push_back(v);
	v = { 1, -1, -1 };
	vertexes.push_back(v);

	// Triangles of cube
	triangle_indexes t;
	t.v[0].n_ind = 0; t.v[1].n_ind = 0; t.v[2].n_ind = 0;
	t.v[0].t_ind = 0; t.v[1].t_ind = 0; t.v[2].t_ind = 0;
	t.v[0].ind = 0; t.v[1].ind = 1; t.v[2].ind = 2;
	face_indexes.push_back(t);
	t.v[0].ind = 0; t.v[1].ind = 2; t.v[2].ind = 3;
	face_indexes.push_back(t);
	t.v[0].ind = 4; t.v[1].ind = 0; t.v[2].ind = 3;
	face_indexes.push_back(t);
	t.v[0].ind = 4; t.v[1].ind = 3; t.v[2].ind = 7;
	face_indexes.push_back(t);
	t.v[0].ind = 5; t.v[1].ind = 4; t.v[2].ind = 7;
	face_indexes.push_back(t);
	t.v[0].ind = 5; t.v[1].ind = 7; t.v[2].ind = 6;
	face_indexes.push_back(t);
	t.v[0].ind = 1; t.v[1].ind = 5; t.v[2].ind = 6;
	face_indexes.push_back(t);
	t.v[0].ind = 1; t.v[1].ind = 6; t.v[2].ind = 2;
	face_indexes.push_back(t);
	t.v[0].ind = 4; t.v[1].ind = 5; t.v[2].ind = 1;
	face_indexes.push_back(t);
	t.v[0].ind = 4; t.v[1].ind = 1; t.v[2].ind = 0;
	face_indexes.push_back(t);
	t.v[0].ind = 2; t.v[1].ind = 6; t.v[2].ind = 7;
	face_indexes.push_back(t);
	t.v[0].ind = 2; t.v[1].ind = 7; t.v[2].ind = 3;
	face_indexes.push_back(t);

	//
	texture_coords.push_back({ 0., 0. });
	normals.push_back({0., 0., 0.});
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
	f >> vt.x >> vt.y;
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
