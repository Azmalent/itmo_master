#pragma once

#include "game.h"
#include "shader.h"

#include <DirectXMath.h>
#include <memory.h>
#include <vector>

struct Vertex
{
	Vector3 pos = Vector3::Zero;
	Vector4 color = Vector4(0, 0, 0, 1);

public:
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, Vector3 color);
	Vertex(float x, float y, float z, Vector4 color);
};

struct Mesh
{
	std::unique_ptr<VertexShader> vertexShader;
	std::unique_ptr<PixelShader> pixelShader;
	ComPtr<ID3D11InputLayout> layout;

	ComPtr<ID3D11Buffer> indexBuffer;
	ComPtr<ID3D11Buffer> vertexBuffer;

	std::vector<DirectX::XMFLOAT4> points;
	std::vector<int> indexes;

	UINT strides[1] = { 32 };
	UINT offsets[1] = { 0 };

	Mesh(Game& game, VertexShader* vertexShader, PixelShader* pixelShader, std::vector<Vertex>& vertices, std::vector<Vector3>& tris);
	~Mesh() = default;
};