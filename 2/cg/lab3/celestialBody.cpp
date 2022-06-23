#include "include/celestialBody.h"

#include <components/mesh.h>
#include <colors.h>
#include <iostream>
#include <shapes.h>
#include <transform.h>

CelestialBodyComponent::CelestialBodyComponent(Game& game, float radius, Vector3 color, float orbitRadius, float orbitPeriod)
	: SceneComponent(game), orbitRadius(orbitRadius), orbitTimer(orbitPeriod, true), rotationTimer(10, true)
{
	auto material = new Material{
		.vertexShader = std::make_unique<VertexShader>(game, L"shaders/vertexShader.hlsl", nullptr, nullptr),
		.pixelShader = std::make_unique<PixelShader>(game, L"shaders/pixelShader.hlsl", nullptr, nullptr)
	};

	std::cout << "sizeof(MaterialData): " << sizeof(MaterialData) << std::endl;
	std::cout << "sizeof(PointLightData): " << sizeof(CelestialBodyComponent::PointLightData) << std::endl;
	std::cout << "sizeof(PixelConstBuffer): " << sizeof(CelestialBodyComponent::PixelConstBuffer) << std::endl;

	material->vertexShader->SetConstBuffer(&vertexConstBuffer, sizeof(CelestialBodyComponent::VertexConstBuffer));
	material->pixelShader->SetConstBuffer(&pixelConstBuffer, sizeof(CelestialBodyComponent::PixelConstBuffer));

	pixelConstBuffer.material = material->data;
	pixelConstBuffer.pointLight = {
		.diffuseColor = Vector4(1, 1, 1, 1),
		.specularColor = Vector4(1, 1, 1, 1),
		.position = Vector4(0, 0, 0, 0),
		.specularPower = 1.0f,
		.innerRadius = 100.0f,
		.outerRadius = 250.0f
	};

	pixelConstBuffer.ambientLight = Vector4(0.25f, 0.25f, 0.25f, 0);

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

	vertexConstBuffer.wvpMatrix = game.Camera.GetWVPMatrix(transform);
	
	auto worldMatrix = transform.GetWorldMatrix();
	auto transposed = XMMatrixTranspose(worldMatrix);
	XMStoreFloat4x4(&vertexConstBuffer.worldMatrix, transposed);

	auto pos = game.Camera.Position;
	pixelConstBuffer.cameraPos = Vector4(pos.x, pos.y, pos.z, 0);
}