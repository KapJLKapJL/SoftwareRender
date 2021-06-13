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

pixel_ARGB Texture::getPixel(const double u, const double v)
{
	int x = int(u * width) % width;
	int y = int(v * height) % height;

	std::cout << x << std::endl;
	std::cout << y << std::endl;

	pixel_ARGB p;

	// ”паковали, так упаковали, мды
	p.R = bits[x * 4 + y * height + 0];
	p.G = bits[x * 4 + y * height + 1];
	p.B = bits[x * 4 + y * height + 2];
	p.A = bits[x * 4 + y * height + 3];

	return p;
}
