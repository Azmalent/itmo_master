#pragma once

class Game;

class GameComponent
{
protected:
	Game& game;

	GameComponent(Game& game) : game(game) { }

public:
	~GameComponent() { }

	virtual void Init() { }
	virtual void Draw() { }
	virtual void Update(float deltaTime) { }
	void Destroy() { }
};