#ifndef WINDOW_H
#define WINDOW_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

LRESULT CALLBACK staticWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class Window
{
public:
	Window();
	~Window();

	bool create();
	LRESULT CALLBACK winProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


	static Window* get() { return win_instance; }

	HWND getHWND() { return hwnd; }

	bool run();
	bool isExit() { return is_exit; }

private:
	static Window* win_instance;
	HWND hwnd;
	bool is_exit;

};

#endif // !WINDOW_H
