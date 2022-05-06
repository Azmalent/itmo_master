#pragma once

#include <game.h>
#include <component.h>

#include "ball.h"

class PaddleComponent;

class AbstractController : public GameComponent
{
protected:
	PaddleComponent& paddle;
	AbstractController(Game& game, PaddleComponent& paddle);

public:
	virtual void Update(float deltaTime) = 0;
};



class PlayerController : public AbstractController
{
public:
	PlayerController(Game& game, PaddleComponent& paddle);
	virtual void Update(float deltaTime);
};



class AIController : public AbstractController
{
private:
	BallComponent& ball;

public:
	AIController(Game& game, PaddleComponent& paddle, BallComponent& ball);
	virtual void Update(float deltaTime);
};