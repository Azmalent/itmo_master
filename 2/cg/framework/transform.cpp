#include "pch.h"

void Transform::SetPosition(float x, float y, float z)
{
	this->position = Vector3(x, y, z);
}

void Transform::OffsetPosition(float deltaX, float deltaY, float deltaZ)
{
	this->position += Vector3(deltaX, deltaY, deltaZ);
}

void Transform::SetScale(float scale)
{
	this->scale = Vector3(scale, scale, scale);
}

void Transform::SetScale(float x, float y, float z)
{
	this->scale = Vector3(x, y, z);
}

Vector3 Transform::GetAbsolutePosition()
{
	if (parent != nullptr) return position + parent->GetAbsolutePosition();
	return position;
}

XMMATRIX Transform::GetWorldMatrix()
{
	auto scaleMatrix = XMMatrixScalingFromVector(scale);
	auto translationMatrix = XMMatrixTranslationFromVector(position);
	auto rotationMatrix = XMMatrixRotationQuaternion(rotation);

	return scaleMatrix * translationMatrix * rotationMatrix;
}