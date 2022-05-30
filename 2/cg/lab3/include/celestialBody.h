#pragma once

#include <components/scene.h>
#include <timer.h>

#include <d3d11.h>
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

class CelestialBodyComponent : public SceneComponent
{
protected:
	struct ConstBuffer {
		XMFLOAT4X4 wvpMatrix;
	};

	float orbitRadius;
	Timer orbitTimer;
	Timer rotationTimer;

	ConstBuffer constBuffer;

public:
	CelestialBodyComponent(Game& game, float radius, Vector3 color, float orbitRadius, float orbitPeriod);
	void Update(float deltaTime);
};