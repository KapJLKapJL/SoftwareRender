#ifndef ABSTRCT_MESH_H
#define ABSTRCT_MESH_H

#include <vector>

#include "MyMath.h"

class abstrctMesh
{
public:
	virtual ~abstrctMesh() {};

	unsigned int getFacesVectorSize() { return faces_vector_size; }

	face getFace(unsigned int face_number)
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
	};
	
	double getMaxRadius() { return max_radius; }

protected:
	std::vector<point3D>  vertexes;
	std::vector<point2D>  texture_coords;
	std::vector<point3D>  normals;
	std::vector<triangle_indexes> face_indexes;
	unsigned int faces_vector_size{ 0 };
	double max_radius{ 0. };

private:
	virtual void readVertexes() = 0;
	virtual void readTextureCoords() = 0;
	virtual void readNormals() = 0;
	virtual void readFaceIndexes() = 0;
};

#endif // !ABSTRCT_MESH_H

