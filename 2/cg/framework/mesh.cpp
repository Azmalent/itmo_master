#include "pch.h"

Mesh::Mesh(Game& game, VertexShader* vertexShader, PixelShader* pixelShader, DirectX::XMFLOAT4* points, int pointsSize, int* indexes, int indexesSize)
	: vertexShader(vertexShader), pixelShader(pixelShader), 
	  points(points), pointsSize(pointsSize), 
	  indexes(indexes), indexesSize(indexesSize)
{
	//Vertex buffer
	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC {
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		}
	};

	game.Render.Device->CreateInputLayout(
		inputElements,
		std::size(inputElements),
		vertexShader->byteCode->GetBufferPointer(),
		vertexShader->byteCode->GetBufferSize(),
		&layout
	);

	D3D11_BUFFER_DESC vertexBufDesc = {
		.ByteWidth = sizeof(DirectX::XMFLOAT4) * pointsSize,
		.Usage = D3D11_USAGE_DEFAULT,
		.BindFlags = D3D11_BIND_VERTEX_BUFFER,
		.CPUAccessFlags = 0,
		.MiscFlags = 0,
		.StructureByteStride = 0
	};

	D3D11_SUBRESOURCE_DATA vertexData = {
		.pSysMem = points,
		.SysMemPitch = 0,
		.SysMemSlicePitch = 0
	};

	game.Render.Device->CreateBuffer(&vertexBufDesc, &vertexData, &vertexBuffer);

	//Index buffer
	D3D11_BUFFER_DESC indexBufDesc = {
		.ByteWidth = sizeof(int) * indexesSize,
		.Usage = D3D11_USAGE_DEFAULT,
		.BindFlags = D3D11_BIND_INDEX_BUFFER,
		.CPUAccessFlags = 0,
		.MiscFlags = 0,
		.StructureByteStride = 0
	};

	D3D11_SUBRESOURCE_DATA indexData = {
		.pSysMem = indexes,
		.SysMemPitch = 0,
		.SysMemSlicePitch = 0
	};

	game.Render.Device->CreateBuffer(&indexBufDesc, &indexData, &indexBuffer);
}

Mesh::~Mesh()
{
	delete pixelShader;
	delete vertexShader;
}