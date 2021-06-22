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

color Texture::getPixel(const double u, const double v)
{
	int x = int(u * width) % width;
	int y = int(v * height) % height;

	color p;

	p.R = bits[(x + y * width) * 4 + 0];
	p.G = bits[(x + y * width) * 4 + 1];
	p.B = bits[(x + y * width) * 4 + 2];
	p.A = bits[(x + y * width) * 4 + 3];

	return p;
}
