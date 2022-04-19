#pragma once

#include <unordered_set>
#include <Windows.h>

class Game;

class InputDevice
{
protected:
	Game* game;
	std::unordered_set<USHORT> pressedKeys;
	LPPOINT previousCursorPos;

public:
	InputDevice(Game* game);
	
	void AddPressedKey(USHORT keycode);
	void RemovePressedKey(USHORT keycode);
	bool IsKeyDown(USHORT keycode);
	
	virtual void OnKeyDown(int keycode);
	virtual void OnMouseMove(LPPOINT newCursorPos);
};