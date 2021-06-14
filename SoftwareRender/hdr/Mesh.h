#ifndef MESH_H
#define MESH_H

#include "MyMath.h"

#include <vector>

class Mesh
{
public:
	Mesh(char const *filename);
	~Mesh();

private:
	std::vector<point3D>  vertexes;
	void loadVertexes(char const* filename);
	std::vector<point2D>  texture_coords;
	void loadTextureCoords(char const* filename);
	std::vector<point3D>  normals;  // Прпидумать другое название для point3D
	void loadNormals(char const* filename);
	//std::vector<Triangle> faces;
};

#endif // !MESH_H

