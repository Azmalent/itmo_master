#pragma once

#include <components/scene.h>
#include <material.h>
#include <timer.h>

#include <d3d11.h>
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

class CelestialBodyComponent : public SceneComponent
{
protected:
#pragma pack(push, 4)
	struct VertexConstBuffer {
		XMFLOAT4X4 wvpMatrix;
		XMFLOAT4X4 worldMatrix;
	};

	struct PointLightData {
		Vector4 diffuseColor;
		Vector4 specularColor;
		Vector4 position;
		float specularPower;
		float innerRadius;
		float outerRadius;
		float _padding[1];
	};

	struct PixelConstBuffer {
		MaterialData material;		//32
		PointLightData pointLight;	//80
		Vector4 ambientLight;		//96
		Vector4 cameraPos;			//112
	};
#pragma pack(pop)

	float orbitRadius;
	Timer orbitTimer;
	Timer rotationTimer;

	VertexConstBuffer vertexConstBuffer;
	PixelConstBuffer pixelConstBuffer;

public:
	CelestialBodyComponent(Game& game, float radius, Vector3 color, float orbitRadius, float orbitPeriod);
	void Update(float deltaTime);
};