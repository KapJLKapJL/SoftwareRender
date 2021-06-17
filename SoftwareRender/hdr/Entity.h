#ifndef ENTITY_H
#define ENTITY_H

#include "Mesh.h"
#include "Texture.h"
#include "MyMath.h"

class Entity
{
public:
	Entity(){};
	~Entity() {};

	void setDiffuseMap(Texture* texture) { diffuse_map = texture; }

	void setMesh(Mesh* mesh_) { mesh = mesh_; }

	face getFace();
	bool eof();
private:
	Texture* diffuse_map{nullptr};

	Mesh* mesh{nullptr};
	unsigned int face_count{0};
};

#endif // !ENTITY_H

