#ifndef MY_DDRAW_H
#define MY DDRAW_H

#define INITGUID
#include <ddraw.h>
#include <wrl.h>

#include <iostream>

#include "Window.h"
#include "MyMath.h"

namespace MWRL = Microsoft::WRL;

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

		MWRL::ComPtr<IDirectDraw7>          i_ddraw;
		MWRL::ComPtr<IDirectDrawSurface7>	i_primary_surface;
		MWRL::ComPtr<IDirectDrawSurface7>   i_back_buffer;

		std::unique_ptr<double[]> z_buffer;;
	};

}//namespace ssr

#endif // !MY_DDRAW_H