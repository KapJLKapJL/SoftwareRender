#ifndef MY_DDRAW_H
#define MY DDRAW_H

#define INITGUID
#include <ddraw.h>

#include <iostream>

#include "Window.h"
#include "Entity.h"
#include "MyMath.h"
#include "AbstractShader.h"

class DDraw
{
public:
	DDraw();
	~DDraw();

	static DDraw* get() { return ddraw_instance; }
	Window* getWindow() { return &window; }

	bool isOpen(){ return window.run(); }

	bool create();
	bool draw(Entity *entity, abstrctShader *shader);
	bool clear();
	bool display();

	void rasterize(matrix<3, 2> &p, Texture* texture, const DDSURFACEDESC2& desc, abstrctShader* shader);
	void barRastrize(const matrix<3, 2> &p, Texture* texture, const DDSURFACEDESC2& desc, abstrctShader* shader);

private:
	static DDraw*	ddraw_instance;
	Window			window;

	LPDIRECTDRAW7			i_ddraw;
	LPDIRECTDRAWSURFACE7	i_primary_surface;
	LPDIRECTDRAWSURFACE7	i_back_buffer;

};

#endif // !MY_DDRAW_H