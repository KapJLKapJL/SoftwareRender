#include "..\hdr\Mesh.h"

#include <iostream>
#include <fstream>

Mesh::Mesh(char const* filename)
{
	loadVertexes(filename);
	//loadTextureCoords(filename);
	//loadNormals(filename);
}

Mesh::~Mesh()
{
}

void Mesh::loadVertexes(char const* filename)
{
	std::ifstream file(filename);

	if (!file)
		return;

	point3D v;
	std::string s;
	while (!file.eof())
	{
		file >> s;
		
		if (s == "v")
		{
			file >> v.x >> v.y >> v.z;
			vertexes.push_back(v);
		}
	}

	file.close();
}
