#include "include/game.h"
#include "include/shader.h"

#include <d3dcompiler.h>
#include <directxmath.h>
#include <iostream>

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		case WM_KEYDOWN:
		{
			unsigned int keycode = static_cast<unsigned int>(wparam);


			if (keycode == 27) PostQuitMessage(0);
			return 0;
		}
		default:
		{
			return DefWindowProc(hwnd, umessage, wparam, lparam);
		}
	}
}

Game::Game(LPCWSTR gameName) : Window(800, 800, gameName, WndProc), Render(Window), Input(this)
{

}

void Game::Init()
{

}

void Game::Run()
{
	Init();

	auto prevTime = std::chrono::steady_clock::now();
	float totalTime = 0;
	unsigned int frameCount = 0;

	MSG msg = {};
	bool isExitRequested = false;
	while (!isExitRequested) 
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) 
		{
			isExitRequested = true;
		}

		auto curTime = std::chrono::steady_clock::now();
		float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - prevTime).count() / 1000000.0f;
		prevTime = curTime;

		Update(deltaTime);

		Render.PreDraw();
		Draw();
		Render.PostDraw(totalTime);
	}
}

void Game::AddComponent(GameComponent* component)
{
	components.insert(components.end(), component);
	component->Init();
}

std::vector<GameComponent*>::iterator Game::DeleteComponent(std::vector<GameComponent*>::iterator it)
{
	GameComponent* current = *it;
	auto next = this->components.erase(it);

	current->Destroy();
	delete current;

	return next;
}

void Game::Update(float deltaTime)
{
	for (auto component : components) 
	{
		component->Update(deltaTime);
	}
}

void Game::Draw()
{
	for (auto component : components) 
	{
		component->Draw();
	}
}