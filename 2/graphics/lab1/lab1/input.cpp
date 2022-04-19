#include "include/input.h"

InputDevice::InputDevice(Game* game) : game(game)
{
	
}

void InputDevice::AddPressedKey(USHORT keycode)
{
	pressedKeys.insert(keycode);
}

void InputDevice::RemovePressedKey(USHORT keycode)
{
	pressedKeys.erase(keycode);
}

bool InputDevice::IsKeyDown(USHORT keycode)
{
	return pressedKeys.contains(keycode);
}

void InputDevice::OnKeyDown(int keycode)
{
	//TODO
}

void InputDevice::OnMouseMove(LPPOINT newCursorPos)
{
	//TODO
}