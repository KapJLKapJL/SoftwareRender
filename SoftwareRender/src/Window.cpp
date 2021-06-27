#include "../hdr/Window.h"

#define WINDOW_CLASS_NAME L"SRWC"

namespace ssr
{

	Window* Window::win_instance = nullptr;

	Window::Window() : hwnd(0), is_exit(false)
	{
		if (!win_instance)
			win_instance = this;
	}

	Window::~Window()
	{
		win_instance = nullptr;
	}

	bool Window::create()
	{
		WNDCLASSEX winclass;

		winclass.cbSize = sizeof(WNDCLASSEX);
		winclass.style = CS_VREDRAW | CS_HREDRAW;
		winclass.lpfnWndProc = staticWndProc;
		winclass.cbClsExtra = 0;
		winclass.cbWndExtra = 0;
		winclass.hInstance = 0;
		winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		winclass.lpszMenuName = NULL;
		winclass.lpszClassName = WINDOW_CLASS_NAME;
		winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&winclass))
			return false;

		hwnd = CreateWindowEx(NULL,
			WINDOW_CLASS_NAME,
			L"SimpleSoftwareRender", // Tetris, lol
			WS_POPUP | WS_VISIBLE, // Сюда WS_POPUP
			0, 0,
			800, 600,
			NULL,
			NULL,
			NULL,
			NULL);

		DWORD ERR = GetLastError();

		if (!hwnd)
			return false;

		return true;
	}

	LRESULT CALLBACK Window::winProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		HDC hdc;
		PAINTSTRUCT ps;

		switch (msg)
		{
		case WM_CREATE:
			return 0;
		case WM_CLOSE:
			is_exit = true;
			return 0;
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_SIZE:
			if (wparam == SIZE_MINIMIZED)
			{
				is_exit = true;
				return 0;
			}
			break;
		case WM_KEYDOWN:
			if (wparam == VK_ESCAPE)
			{
				SendMessage(hwnd, WM_CLOSE, 0, 0);
				return 0;
			}
			break;
		default:
			break;
		}
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	LRESULT CALLBACK staticWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		return Window::get()->winProc(hwnd, msg, wparam, lparam);
	}

	bool Window::run()
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) return false;

			TranslateMessage(&msg);   //Транслируем сообщение
			DispatchMessage(&msg);    //Обрабатываем сообщение
		}
		return true;
	}

}//namespace ssr