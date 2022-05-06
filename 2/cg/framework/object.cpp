#include "pch.h"

Vector3 Transform::GetAbsolutePosition()
{
	if (parent != nullptr) return position + parent->GetAbsolutePosition();
	return position;
}

XMFLOAT4X4 Transform::GetTranslationMatrix()
{
	auto p = GetAbsolutePosition();
	return XMFLOAT4X4(
		1,	 0,	 0,	   0,
		0,	 1,	 0,	   0,
		0,	 0,	 1,	   0,
		p.x, p.y, p.z, 1
	);
}

XMFLOAT4X4 Transform::GetRotationMatrix()
{
	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, XMMatrixRotationQuaternion(rotation));
	return matrix;
}

XMFLOAT4X4 Transform::GetScaleMatrix()
{
	return XMFLOAT4X4(
		scale, 0, 0, 0,
		0, scale, 0, 0,
		0, 0, scale, 0,
		0, 0, 0, 1
	);
}

XMFLOAT4X4 Transform::GetWorldViewProjection()
{
	return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
}

GameObject::GameObject(Game& game) : GameComponent(game)
{

}

void GameObject::SetParent(GameObject& parent)
{
	Transform.parent = &parent.Transform; //todo: check for loops
}