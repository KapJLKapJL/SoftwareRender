#include "..\hdr\Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

Texture::Texture(char const* filename):bits(nullptr)
{
	bits = stbi_load(filename, &width, &height, &nmbr_chanels, 4);
}

Texture::~Texture()
{
	stbi_image_free(bits);
}

color Texture::getPixel(const double &u, const double &v)
{
	int x = int(u * width) % width;
	int y = int(v * height) % height;

	color p;

	int pixel_count = (x + y * width) * 4;
	p.R = bits[pixel_count + 0];
	p.G = bits[pixel_count + 1];
	p.B = bits[pixel_count + 2];
	p.A = bits[pixel_count + 3];

	return p;
}
