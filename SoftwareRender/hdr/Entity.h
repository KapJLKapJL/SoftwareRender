#ifndef ENTITY_H
#define ENTITY_H

#include "Mesh.h"
#include "Texture.h"
#include "MyMath.h"
#include "AbstractMesh.h"

class Entity
{
public:
	Entity(){};
	~Entity() {};

	void setDiffuseMap(Texture* texture) { diffuse_map = texture; }
	Texture* getDiffuseMap() { return diffuse_map; }

	void setMesh(abstrctMesh* mesh_) { mesh = mesh_; }

	face getFace();
	bool eof();

	void setPosition(const point3D &t);
	void setRotationX(const double &angle);
	void setRotation(const double& alpha, const double& beta, const double& gamma);

	matrix<4, 4> getModelMatrix() { return model; };
private:
	Texture* diffuse_map{nullptr};

	abstrctMesh* mesh{nullptr};
	unsigned int face_count{0};

	matrix<4, 4> model{ {1., 0., 0., 0.,
		                 0., 1., 0., 0.,
		                 0., 0., 1., 0.,
		                 0., 0., 0., 1.} };
};

#endif // !ENTITY_H

