#include "pch.h"

PositionedComponent::PositionedComponent(Game& game) : GameComponent(game)
{

}

Transform* PositionedComponent::GetTransform()
{
	return &transform;
}

void PositionedComponent::SetParent(GameComponent* parent)
{
	if (parent != nullptr && CanBeChildOf(parent))
	{
		this->parent = parent;

		auto parentTransform = parent->GetTransform();
		auto newPos = transform.GetAbsolutePosition();

		if (parentTransform != nullptr)
		{
			newPos -= parentTransform->GetAbsolutePosition();
		}

		transform.parent = parentTransform;
		transform.position = newPos;
	}
}