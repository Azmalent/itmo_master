#pragma once

#include "game.h"
#include "shader.h"

#include <DirectXMath.h>
#include <memory.h>

struct Mesh
{
	std::unique_ptr<VertexShader> vertexShader;
	std::unique_ptr<PixelShader> pixelShader;
	ComPtr<ID3D11InputLayout> layout;

	ComPtr<ID3D11Buffer> indexBuffer;
	ComPtr<ID3D11Buffer> vertexBuffer;

	DirectX::XMFLOAT4* points;
	int pointsSize;

	int* indexes;
	int indexesSize;

	UINT strides[1] = { 32 };
	UINT offsets[1] = { 0 };

	Mesh(Game& game, VertexShader* vertexShader, PixelShader* pixelShader, DirectX::XMFLOAT4* points, int pointsSize, int* indexes, int indexesSize);
	~Mesh() = default;
};