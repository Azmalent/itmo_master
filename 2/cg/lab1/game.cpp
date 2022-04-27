#include "include/game.h"
#include "include/shader.h"

#include <d3dcompiler.h>
#include <directxmath.h>
#include <iostream>

static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	switch (umessage)
	{
		case WM_SIZE:
		{
			if (window != nullptr)
			{
				window->ClientWidth = LOWORD(lparam);
				window->ClientHeight = LOWORD(lparam);
				return 0;
			}
		}
		case WM_INPUT:
		{
			if (window != nullptr && window->Input != nullptr)
			{
				window->Input->OnInput(lparam);
			}
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

Game::Game(LPCWSTR gameName, WNDPROC messageHandler) : Window(800, 800, gameName, messageHandler), Render(Window), Input(this)
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
	bool exitRequested = false;
	while (!exitRequested) 
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) 
		{
			exitRequested = true;
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