#ifndef TEXTURE_H
#define TEXTURE_H

#include "MyMath.h"

namespace ssr
{


	class Texture
	{
	public:
		Texture(char const* filename);
		~Texture();

		int getWidth() { return width; }
		int getHeigth() { return height; }
		int getNumberChanels() { return nmbr_chanels; }

		color getPixel(const double& u, const double& v);
	private:
		unsigned char* bits;
		int width;
		int height;
		int nmbr_chanels;
	};

}//namespace ssr

#endif // !TEXTURE_H

