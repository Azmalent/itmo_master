﻿// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <colors.h>
#include <game.h>
#include <components/fpsCounter.h>
#include <components/mesh.h>
#include <shader.h>

#include <directxmath.h>
#include <iostream>
#include <windows.h>
#include <WinUser.h>
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//using namespace DirectX::SimpleMath;

class TriangleGame : public Game
{
private:
	bool exitRequested = false;

public:
	TriangleGame(LPCWSTR gameName) : Game(gameName) 
	{ 
		//Счётчик FPS
		auto fpsCounter = new FpsCounterComponent(*this);
		AddComponent(fpsCounter);

		//Инициализация шейдеров
		auto vertexShader = new VertexShader(*this, L"shaders/vertexShader.hlsl", nullptr, nullptr);
		auto pixelShader = new PixelShader(*this, L"shaders/pixelShader.hlsl", nullptr, nullptr);

		//Меш
		std::vector<Vertex> vertices = {
			Vertex(0.5f, 0.5f, 0.5f, Colors::Red),
			Vertex(-0.5f, -0.5f, 0.5f, Colors::Blue),
			Vertex(0.5f, -0.5f, 0.5f, Colors::Green),
			Vertex(-0.5f, 0.5f, 0.5f, Colors::White)
		};

		std::vector<Vector3> tris = {
			{0, 1, 2}, {1, 0, 3}
		};

		auto mesh = new Mesh(*this, vertexShader, pixelShader, vertices, tris);

		//Компонент меша
		auto meshComponent = new MeshComponent(*this, mesh);
		AddComponent(meshComponent);
	}

	void Init()
	{
		Input.KeyPressedEvent.AddLambda([this](const Key keycode) {
			std::cout << "Key pressed: " << ToString(keycode) << std::endl;
			if (keycode == Key::Esc)
			{
				this->exitRequested = true;
				return 0;
			}
		});

		Input.KeyReleasedEvent.AddLambda([](const Key keycode) {
			std::cout << "Key released: " << ToString(keycode) << std::endl;
		});

		Input.MouseMoveEvent.AddLambda([this](const MouseMoveArgs& args) {
			auto pos = args.Position;
			auto vpos = this->Window.PixelToViewportPos(pos);
			std::cout << "Mouse moved: (" << pos.x << ", " << pos.y << ")";
			std::cout << " (" << vpos.x << ", " << vpos.y << ")" << std::endl;
		});
	}

	void Update(float deltaTime)
	{
		Game::Update(deltaTime);
		if (exitRequested) Window.Close(0);
	}
};

int main()
{
	TriangleGame game = TriangleGame(L"Lab1");
	game.Run();

	return 0;
}