#ifndef TEXTURE_H
#define TEXTURE_H

#include "MyMath.h"

class Texture
{
public:
	Texture(char const *filename);
	~Texture();

	int getWidth() { return width; }
	int getHeigth() { return height; }
	int getNumberChanels() { return nmbr_chanels; }

	pixel_ARGB getPixel(const double u, const double v);
private:
	unsigned char* bits;
	int width;
	int height;
	int nmbr_chanels;
};

#endif // !TEXTURE_H

