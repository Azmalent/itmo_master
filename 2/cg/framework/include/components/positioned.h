#pragma once

#include "../component.h"
#include "../delegates.h"
#include "../transform.h"

class PositionedComponent : public GameComponent
{
public:
	Transform transform;

	MulticastDelegate<PositionedComponent*> CollisionStartEvent;
	MulticastDelegate<PositionedComponent*> CollisionEndEvent;

	PositionedComponent(Game& game);

	Transform* GetTransform();
	void SetParent(GameComponent* parent);
};