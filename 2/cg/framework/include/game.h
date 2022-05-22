#pragma once

#include "camera.h"
#include "components/collider.h"
#include "input.h"
#include "render.h"

#include <d3d.h>
#include <d3d11.h>
#include <chrono>
#include <vector>

class Game
{
	friend class BoxColliderComponent;

protected:
	std::vector<GameComponent*> components;
	std::vector<BoxColliderComponent*> boxColliders;

	virtual void Init();
	virtual void Draw();
	virtual void Update(float deltaTime);
	virtual void Destroy();

	std::vector<GameComponent*>::iterator DeleteComponent(std::vector<GameComponent*>::iterator it);

public:
	Window Window;
	Camera Camera;
	RenderDevice Render;
	InputDevice Input;

	void AddComponent(GameComponent* component);
	void DeleteComponent(GameComponent* component);

	Game(LPCWSTR gameName);
	Game(LPCWSTR gameName, WNDPROC messageHandler);
	void Run();
};