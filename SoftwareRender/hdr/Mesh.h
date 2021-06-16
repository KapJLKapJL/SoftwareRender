#ifndef MESH_H
#define MESH_H

#include "MyMath.h"

#include <vector>
#include <fstream>

class Mesh
{
public:
	Mesh(char const *filename);
	~Mesh();

private:
	std::vector<point3D>  vertexes;
	void readVertexes(std::ifstream& file);

	std::vector<point2D>  texture_coords;
	void readTextureCoords(std::ifstream& file);

	std::vector<point3D>  normals;  // Прпидумать другое название для point3D
	void readNormals(std::ifstream& file);

	std::vector<triangle_indexes> face_indexes;
	void readFaceIndexes(std::ifstream& file);
};

#endif // !MESH_H

