#ifndef MY_DDRAW_H
#define MY DDRAW_H

#define INITGUID
#include <ddraw.h>

#include <iostream>

#include "Window.h"
#include "MyMath.h"

namespace ssr
{
	class Texture;
	class Entity;
	class abstrctShader;

	class DDraw
	{
	public:
		DDraw();
		~DDraw();

		static DDraw* get() { return ddraw_instance; }
		Window* getWindow() { return &window; }

		bool isOpen() { return window.run(); }
		bool isExit() { return window.isExit(); }

		bool create();
		bool draw(Entity* entity, abstrctShader* shader);
		bool clear();
		bool display();

		void barRastrize(const matrix<3, 3>& v, Texture* texture, abstrctShader* shader);

	private:
		static DDraw* ddraw_instance;
		Window		window;

		LPDIRECTDRAW7			i_ddraw;
		LPDIRECTDRAWSURFACE7	i_primary_surface;
		LPDIRECTDRAWSURFACE7	i_back_buffer;

		double* z_buffer;
	};

}//namespace ssr

#endif // !MY_DDRAW_H