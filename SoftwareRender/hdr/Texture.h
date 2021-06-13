#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
	Texture(char const *filename);
	~Texture();

	int getWidth() { return width; }
	int getHeigth() { return height; }
	int getNumberChanels() { return nmbr_chanels; }
private:
	unsigned char* bits;
	int width;
	int height;
	int nmbr_chanels;
	unsigned char null{0};
};

#endif // !TEXTURE_H

