#include "include/paddle.h"

#include <algorithm>
#include <iostream>

static const float halfWidth = 0.025f;
static const float halfHeight = 0.25f;

PaddleComponent::PaddleComponent(Game& game, BallComponent& ball) : SceneComponent(game), ball(ball)
{
	auto vertexShader = new VertexShader(game, L"shaders/vertexShader.hlsl", nullptr, nullptr);
	vertexShader->SetConstBuffer(&constBuffer, sizeof(PaddleComponent::ConstBuffer));
	
	auto pixelShader = new PixelShader(game, L"shaders/pixelShader.hlsl", nullptr, nullptr);

	//Меш
	DirectX::XMFLOAT4 points[] = {
		DirectX::XMFLOAT4(halfWidth, halfHeight, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(-halfWidth, -halfHeight, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(halfWidth, -halfHeight, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(-halfWidth, halfHeight, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	};

	int indexes[] = {
		0,1,2,
		1,0,3
	};

	auto mesh = new Mesh(game,
		vertexShader, pixelShader,
		points, std::size(points),
		indexes, std::size(indexes)
	);

	AddChild(new MeshComponent(game, mesh));
	AddChild(new BoxColliderComponent(game, Vector3(halfWidth, halfHeight, 0.5f)));
}

void PaddleComponent::Update(float deltaTime)
{
	constBuffer.wvpMatrix = game.Camera.GetWorldViewProjectionMatrix(transform);
}

void PaddleComponent::SetSpeed(float speed)
{
	this->speed = speed;
}