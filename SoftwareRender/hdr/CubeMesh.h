#ifndef CUBE_MESH_H
#define CUBE_MESH_H

#include "AbstractMesh.h"

class CubeMesh : public abstrctMesh
{
public:
	CubeMesh();
	virtual ~CubeMesh() {};
private:
	void readVertexes() override;
	void readTextureCoords() override;
	void readNormals() override;
	void readFaceIndexes() override;
};

#endif // !CUBE_MESH_H

