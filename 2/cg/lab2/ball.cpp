#include "include/ball.h"
#include "include/paddle.h"

#include <components/collider.h>
#include <components/mesh.h>

#include <algorithm>
#include <random>

static const float R = 0.025;

static const float MIN_SPEED = 0.33;
static const float MAX_SPEED = 1;

BallComponent::BallComponent(Game& game) : PositionedComponent(game)
{
	auto vertexShader = new VertexShader(game, L"shaders/vertexShader.hlsl", nullptr, nullptr);
	vertexShader->SetConstBuffer(&constBuffer, sizeof(BallComponent::ConstBuffer));

	auto pixelShader = new PixelShader(game, L"shaders/pixelShader.hlsl", nullptr, nullptr);

	//Меш
	DirectX::XMFLOAT4 points[] = {
		DirectX::XMFLOAT4(R, R, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(-R, -R, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(R, -R, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(-R, R, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
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
	AddChild(new BoxColliderComponent(game, Vector3(R, R, 0.5f)));

	CollisionStartEvent.AddLambda([this](PositionedComponent* other) {
		auto paddle = dynamic_cast<PaddleComponent*>(other);
		if (paddle != nullptr)
		{
			auto d = transform.position - paddle->transform.position;
			d.Normalize();

			direction = (Vector2(-direction.x, direction.y) + Vector2(d.x, d.y)) / 2;
			direction.Normalize();
		}
	});

	ResetPosition();
}

void BallComponent::Update(float deltaTime)
{
	Vector2 deltaPos = direction * speed * deltaTime;
	float x = transform.position.x + deltaPos.x;
	float y = transform.position.y + deltaPos.y;

	if (y > 1 || y < -1) direction.y *= -1;
	transform.SetPosition(x, std::clamp(y, -1.0f, 1.0f), 0.5f);

	if (timeUntilMaxSpeed > 0)
	{
		speed = std::lerp(MAX_SPEED, MIN_SPEED, timeUntilMaxSpeed);
		timeUntilMaxSpeed = max(0, timeUntilMaxSpeed - deltaTime);
	}

	constBuffer.wvpMatrix = game.Camera.GetWorldViewProjectionMatrix(transform);
}

void BallComponent::ResetPosition()
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_real_distribution<float> angleDistribution(0, 2 * 3.14f);

	do
	{
		float a = angleDistribution(engine);
		direction = Vector2(cos(a), sin(a));
	} while (abs(direction.y) >= 0.75);

	transform.SetPosition(0, 0, 0.5f);
	
	speed = MIN_SPEED;
	timeUntilMaxSpeed = 1;
}