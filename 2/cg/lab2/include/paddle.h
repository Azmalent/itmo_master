#pragma once

#include <components/mesh.h>
#include <components/object.h>

#include "ball.h"
#include "controller.h"

class PaddleComponent : public GameObject
{
private:
	int speed = 0;
	//MeshComponent mesh;
	AbstractController* controller;
	BallComponent& ball;

public:
	PaddleComponent(Game& game, BallComponent& ball);
	~PaddleComponent() = default;

	virtual void Update(float deltaTime);
	virtual void Draw();

	void SetController(AbstractController* controller);
	void SetSpeed(int speed);
};