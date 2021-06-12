#ifndef MY_DDRAW_H
#define MY DDRAW_H

#include "Window.h"
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

private:
	static DDraw* ddraw_instance;
	Window window;

	LPDIRECTDRAW7 i_ddraw;
};

#endif // !MY_DDRAW_H