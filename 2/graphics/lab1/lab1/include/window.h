#pragma once

#include <windows.h>
#include <WinUser.h>

class Window
{
private:
	HINSTANCE hInstance;
	WNDCLASSEX wc;

public:
	LPCWSTR ApplicationName;
	int ClientHeight;
	int ClientWidth;
	HWND hWnd;

	Window(int width, int height, LPCWSTR applicationName, WNDPROC messageHandler);
};