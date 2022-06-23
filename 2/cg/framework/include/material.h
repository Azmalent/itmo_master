#pragma once

#include <DirectXMath.h>
#include <memory.h>
#include <SimpleMath.h>

#include "shader.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

#pragma pack(push, 4)
struct MaterialData
{
	Vector3 diffuseColor = Vector3::One;	//12
	float diffuse = 1.0f;		//16
	float ambient = 0.8f;		//20
	float specular = 0.5f;		//24
	float shininess = 250.0f;	//28
	float _padding[1];			//32
};
#pragma pack(pop)

struct Material
{
	std::unique_ptr<VertexShader> vertexShader;
	std::unique_ptr<PixelShader> pixelShader;
	MaterialData data;
};