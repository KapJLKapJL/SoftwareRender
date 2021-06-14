#include "..\hdr\Mesh.h"

#include <iostream>

Mesh::Mesh(char const* filename)
{
	std::ifstream file(filename);

	if (!file)
		return; // ???????????

	loadVertexes(file);

	file.clear();
	file.seekg(0, std::ios::beg);
	loadTextureCoords(file);

	file.clear();
	file.seekg(0, std::ios::beg);
	loadNormals(file);

	file.close();
}

Mesh::~Mesh()
{
}

void Mesh::loadVertexes(std::ifstream& f)
{
	point3D v;
	std::string s;
	while (!f.eof())
	{
		f >> s;
		
		if (s == "v")
		{
			f >> v.x >> v.y >> v.z;
			vertexes.push_back(v);
		}
	}
}

void Mesh::loadTextureCoords(std::ifstream& f)
{
	point2D vt;
	std::string s;
	while (!f.eof())
	{
		f >> s;

		if (s == "vt")
		{
			f >> vt.u >> vt.v;
			texture_coords.push_back(vt);
		}
	}
}

void Mesh::loadNormals(std::ifstream& f)
{
	point3D vn;
	std::string s;
	while (!f.eof())
	{
		f >> s;

		if (s == "vn")
		{
			f >> vn.x >> vn.y >> vn.z;
			normals.push_back(vn);
		}
	}
}
