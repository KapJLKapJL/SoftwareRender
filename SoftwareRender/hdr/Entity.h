#ifndef ENTITY_H
#define ENTITY_H

//#include "Texture.h"
#include "MyMath.h"
#include "AbstractMesh.h"


namespace ssr
{
	class Texture;

	class Entity
	{
	public:
		Entity() {};
		~Entity() {};

		void setDiffuseMap(Texture* texture) { diffuse_map = texture; }
		ssr::Texture* getDiffuseMap() { return diffuse_map; }

		void setMesh(abstrctMesh* mesh_)
		{
			mesh = mesh_;
			max_radius = mesh->getMaxRadius();
			resize_coef = 1.;
		}

		face getFace();
		bool eof();

		void setPosition(const point3D& t);
		void setRotationX(const double& angle);
		void setRotation(const double& alpha, const double& beta, const double& gamma);
		void setMaxRadius(const double& radius) { resize_coef = radius / max_radius; }


		matrix<4, 4> getModelMatrix() { return model; };
	private:
		ssr::Texture* diffuse_map{ nullptr };

		abstrctMesh* mesh{ nullptr };
		unsigned int face_count{ 0 };

		matrix<4, 4> model{ {1., 0., 0., 0.,
							 0., 1., 0., 0.,
							 0., 0., 1., 0.,
							 0., 0., 0., 1.} };

		double max_radius{ 0. };
		double resize_coef{ 1. };
	};
}//namespace ssr

#endif // !ENTITY_H

