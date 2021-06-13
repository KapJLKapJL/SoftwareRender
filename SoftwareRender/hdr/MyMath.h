#ifndef MY_MATH_H
#define MY_MATH_H

#pragma pack(push, 1)
union pixel_ARGB
{
	struct { unsigned char B, G, R, A; }; //(0 - A) (1 - R) (2 - G) (3 - B)
	unsigned int ARGB;
};
#pragma pack(pop)

struct point2D
{
	int x, y;
};

struct Triangle2D
{
	point2D a, b, c;
};

#endif // !MY_MATH_H

