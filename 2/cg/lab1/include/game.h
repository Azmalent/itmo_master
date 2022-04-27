#pragma once

#include "components/component.h"
#include "input.h"
#include "render.h"

#include <d3d.h>
#include <d3d11.h>
#include <chrono>
#include <vector>

class Game
{
protected:
	std::vector<GameComponent*> components;

	virtual void Init();
	virtual void Draw();
	virtual void Update(float deltaTime);

public:
	Window Window;
	RenderDevice Render;
	InputDevice Input;

	void AddComponent(GameComponent* component);
	std::vector<GameComponent*>::iterator DeleteComponent(std::vector<GameComponent*>::iterator it);

	Game(LPCWSTR gameName);
	Game(LPCWSTR gameName, WNDPROC messageHandler);
	void Run();
};