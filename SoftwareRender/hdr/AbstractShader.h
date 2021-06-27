#ifndef ABCTRCT_SHADER_H
#define ABCTRCT_SHADER_H

#include "MyMath.h"


namespace ssr
{

	class abstrctShader
	{
	public:
		virtual ~abstrctShader() {};

		void setWorldMatrix(const matrix<4, 4>& to_world_) { to_world = to_world_; };
		void setProjectionMatrix(const matrix<3, 4>& projection_) { projection = projection_; };

		virtual point3D vertex(const face& f, const int& idx) = 0;
		virtual color pixel(const point3D& bar, Texture* t) = 0;

	protected:
		matrix<4, 4> to_world;
		matrix<3, 4> projection;
	};

}//namespace ssr

#endif // !ABCTRCT_SHADER_H

