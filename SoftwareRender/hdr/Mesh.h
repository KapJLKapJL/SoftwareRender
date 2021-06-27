#ifndef MESH_H
#define MESH_H

#include <vector>
#include <fstream>

#include "AbstractMesh.h"

namespace ssr
{

	class Mesh : public abstrctMesh
	{
	public:
		Mesh(char const* filename);
		virtual ~Mesh() {};

	private:
		void readVertexes() override;
		void readTextureCoords() override;
		void readNormals() override;
		void readFaceIndexes() override;

		std::ifstream file;
	};
}//namespace ssr

#endif // !MESH_H

