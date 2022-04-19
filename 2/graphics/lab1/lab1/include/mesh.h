#pragma once

#include "game.h"
#include "shader.h"

#include <DirectXMath.h>

struct Mesh
{
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	ID3D11InputLayout* layout;

	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* vertexBuffer;

	DirectX::XMFLOAT4* points;
	int pointsSize;

	int* indexes;
	int indexesSize;

	UINT strides[1] = { 32 };
	UINT offsets[1] = { 0 };

	Mesh(Game& game, VertexShader* vertexShader, PixelShader* pixelShader, DirectX::XMFLOAT4* points, int pointsSize, int* indexes, int indexesSize);
	~Mesh();
};