#include "pch.h"

SceneComponent::SceneComponent(Game& game) : GameComponent(game)
{

}

Transform* SceneComponent::GetTransform()
{
	return &transform;
}

void SceneComponent::SetParent(GameComponent* parent)
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