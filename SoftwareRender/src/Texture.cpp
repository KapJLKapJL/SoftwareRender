#include "..\hdr\Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(char const* filename):bits(nullptr)
{
	bits = stbi_load(filename, &width, &height, &nmbr_chanels, 4);
}

Texture::~Texture()
{
	stbi_image_free(bits);
}
