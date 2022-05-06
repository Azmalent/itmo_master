#pragma once

#include "../component.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <SimpleMath.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

struct Transform 
{
	Transform* parent = nullptr;

	Vector3 position = Vector3::Zero;
	Quaternion rotation = Quaternion::Identity;
	float scale = 1;

	Vector3 GetAbsolutePosition();

	XMFLOAT4X4 GetTranslationMatrix();
	XMFLOAT4X4 GetRotationMatrix();
	XMFLOAT4X4 GetScaleMatrix();
	XMFLOAT4X4 GetWorldViewProjection();
};

class GameObject : public GameComponent
{
public:
	Transform Transform;

	GameObject(Game& game);

	void SetParent(GameObject& parent);
};