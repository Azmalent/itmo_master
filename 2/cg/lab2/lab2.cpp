// lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <game.h>
#include <iostream>

#include "include/ball.h"
#include "include/paddle.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

class PongGame : public Game
{
private:
	bool exitRequested = false;

public:
	PongGame(LPCWSTR gameName) : Game(gameName) 
	{ 
		Render.SetClearColor(0, 0, 0);

		auto ball = BallComponent(*this);

		auto playerPaddle = PaddleComponent(*this, ball);
		playerPaddle.SetController(new PlayerController(*this, playerPaddle));

		auto aiPaddle = PaddleComponent(*this, ball);
		aiPaddle.SetController(new AIController(*this, aiPaddle, ball));
	}

	virtual void Init()
	{
		Input.KeyPressedEvent.AddLambda([this](const Key keycode) {
			if (keycode == Key::Esc)
			{
				this->exitRequested = true;
				return 0;
			}
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
    auto game = PongGame(L"Pong");
	game.Run();

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
