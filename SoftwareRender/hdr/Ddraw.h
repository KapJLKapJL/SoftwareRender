#ifndef MY_DDRAW_H
#define MY DDRAW_H

#include "Window.h"
#include "Texture.h"

#define INITGUID
#include <ddraw.h>

#include <iostream>



class DDraw
{
public:
	DDraw();
	~DDraw();

	static DDraw* get() { return ddraw_instance; }
	Window* getWindow() { return &window; }

	bool create();
	bool draw(Texture &texture);

private:
	static DDraw*	ddraw_instance;
	Window			window;

	LPDIRECTDRAW7			i_ddraw;
	LPDIRECTDRAWSURFACE7	i_primary_surface;
	LPDIRECTDRAWSURFACE7	i_back_buffer;

};

#endif // !MY_DDRAW_H