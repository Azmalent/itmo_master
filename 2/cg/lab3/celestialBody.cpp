#include "include/celestialBody.h"

#include <components/mesh.h>
#include <shapes.h>
#include <transform.h>

CelestialBodyComponent::CelestialBodyComponent(Game& game, float radius, Vector3 color, float orbitRadius, float orbitPeriod)
	: SceneComponent(game), orbitRadius(orbitRadius), orbitTimer(orbitPeriod, true), rotationTimer(10, true)
{
	auto material = new Material{
		.vertexShader = std::make_unique<VertexShader>(game, L"shaders/vertexShader.hlsl", nullptr, nullptr),
		.pixelShader = std::make_unique<PixelShader>(game, L"shaders/pixelShader.hlsl", nullptr, nullptr)
	};

	material->vertexShader->SetConstBuffer(&constBuffer, sizeof(CelestialBodyComponent::ConstBuffer));

	auto mesh = Shapes::MakeSphere(game, material, radius, 10, 10, color);
	AddChild(new MeshComponent(game, mesh));

	transform.SetPosition(orbitRadius, 0, 0);
}

void CelestialBodyComponent::Update(float deltaTime)
{
	if (orbitRadius > 0)
	{
		orbitTimer.Update(deltaTime);
		rotationTimer.Update(deltaTime);

		float angle = 2.0f * 3.14f * orbitTimer.GetProgress();
		transform.SetPosition(orbitRadius * cos(angle), orbitRadius * sin(angle), 0);

		float rotationAngle = 2.0f * 3.14f * rotationTimer.GetProgress();
		transform.SetRotation(0, rotationAngle, 0);
	}

	constBuffer.wvpMatrix = game.Camera.GetWVPMatrix(transform);
}