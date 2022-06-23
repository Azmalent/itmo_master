#pragma once

#include <DirectXMath.h>
#include <memory.h>
#include <SimpleMath.h>

#include "shader.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

struct Material
{
	std::unique_ptr<VertexShader> vertexShader;
	std::unique_ptr<PixelShader> pixelShader;

	Vector3 diffuseColor = Vector3::One;
	float diffuse = 1.0f;
	float ambient = 0.8f;
	float specular = 0.5f;
	float shininess = 250.0f;
};