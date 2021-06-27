#include <iostream>
#include <sstream>

#include "..\hdr\Mesh.h"

namespace ssr
{

	Mesh::Mesh(char const* filename)
	{
		//std::ifstream file(filename);

		file.open(filename);

		if (!file)
		{
			return;
		}
		else
		{
			std::string s;
			while (!file.eof())
			{
				file >> s;

				if (s == "v")
					readVertexes();
				if (s == "vt")
					readTextureCoords();
				if (s == "vn")
					readNormals();
				if (s == "f")
					readFaceIndexes();

				s = "";
			}
		}
		file.close();

		faces_vector_size = face_indexes.size();
	}

	void Mesh::readVertexes()
	{
		point3D v;
		file >> v.x >> v.y >> v.z;
		vertexes.push_back(v);
		max_radius = std::fmax(max_radius, v.length());
	}

	void Mesh::readTextureCoords()
	{
		point2D vt;
		file >> vt.x >> vt.y;
		vt.y = 1. - vt.y; // WHY????????????????????
		texture_coords.push_back(vt);
	}

	void Mesh::readNormals()
	{
		point3D vn;
		file >> vn.x >> vn.y >> vn.z;
		normals.push_back(vn);
	}

	void Mesh::readFaceIndexes()
	{
		triangle_indexes t;
		std::string s;
		for (int i = 0; i < 3; i++)
		{
			file >> s;
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
}
