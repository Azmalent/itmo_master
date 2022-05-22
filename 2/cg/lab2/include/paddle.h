#pragma once

#include <components/mesh.h>
#include <components/positioned.h>

#include "ball.h"
#include "controller.h"

class PaddleComponent : public PositionedComponent
{
private:
	struct ConstBuffer {
		XMFLOAT4X4 wvpMatrix;
	};

	float speed = 0;
	BallComponent& ball;

	ConstBuffer constBuffer;

public:
	PaddleComponent(Game& game, BallComponent& ball);
	~PaddleComponent() = default;

	virtual void Update(float deltaTime);
	void SetSpeed(float speed);
};