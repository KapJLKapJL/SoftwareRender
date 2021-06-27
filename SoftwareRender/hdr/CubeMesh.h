#ifndef CUBE_MESH_H
#define CUBE_MESH_H

#include "AbstractMesh.h"

namespace ssr
{

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

}//namespace ssr

#endif // !CUBE_MESH_H

