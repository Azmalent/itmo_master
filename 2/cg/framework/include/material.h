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
	Vector4 diffuseColor = Vector4::One;	//16
	float diffuse = 1.0f;		//20
	float ambient = 0.8f;		//24
	float specular = 0.5f;		//28
	float shininess = 250.0f;	//32
};
#pragma pack(pop)

struct Material
{
	std::unique_ptr<VertexShader> vertexShader;
	std::unique_ptr<PixelShader> pixelShader;
	MaterialData data;
};