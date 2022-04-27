#pragma once

#include "input.h"

#include <SimpleMath.h>
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
	InputDevice* Input = nullptr;

	Window(int width, int height, LPCWSTR applicationName, WNDPROC messageHandler);
	void Close(int exitCode);

	Vector2 PixelToViewportPos(Vector2 pos);
};