#include <game.h>
#include <keys.h>

#include "include/paddle.h"

AbstractController::AbstractController(Game& game, PaddleComponent& paddle) : GameComponent(game), paddle(paddle)
{

}

PlayerController::PlayerController(Game& game, PaddleComponent& paddle) : AbstractController(game, paddle)
{

}

void PlayerController::Update(float deltaTime)
{
	if (game.Input.IsKeyDown(Key::Up))
	{
		paddle.SetSpeed(-100);
	}
	else if (game.Input.IsKeyDown(Key::Down))
	{
		paddle.SetSpeed(100);
	}
}

AIController::AIController(Game& game, PaddleComponent& paddle, BallComponent& ball) : AbstractController(game, paddle), ball(ball)
{

}

void AIController::Update(float deltaTime)
{
	//todo
}