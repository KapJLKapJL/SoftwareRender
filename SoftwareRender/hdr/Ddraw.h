#ifndef MY_DDRAW_H
#define MY DDRAW_H

#define INITGUID
#include <ddraw.h>
#include "Window.h"

class DDraw
{
public:
	DDraw();
	~DDraw() {};

	static DDraw* get() { return ddraw_instance; }
	Window* getWindow() { return &window; }
	bool create();

private:
	static DDraw* ddraw_instance;
	Window window;
};

#endif // !MY_DDRAW_H