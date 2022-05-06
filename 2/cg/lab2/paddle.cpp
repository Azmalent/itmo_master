#include "include/paddle.h"

PaddleComponent::PaddleComponent(Game& game, BallComponent& ball) : GameObject(game), ball(ball)
{

}

void PaddleComponent::Update(float deltaTime)
{

}

void PaddleComponent::Draw()
{

}

void PaddleComponent::SetController(AbstractController* controller)
{
	this->controller = controller;
}

void PaddleComponent::SetSpeed(int speed)
{
	this->speed = speed;
}