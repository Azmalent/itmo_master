#include "pch.h"

Vertex::Vertex(float x, float y, float z) : pos(x, y, z)
{

}

Vertex::Vertex(float x, float y, float z, Vector3 color) : pos(x, y, z), color(color.x, color.y, color.z, 1)
{

}

Vertex::Vertex(float x, float y, float z, Vector4 color) : pos(x, y, z), color(color)
{

}

Mesh::Mesh(Game& game, VertexShader* vertexShader, PixelShader* pixelShader, std::vector<Vertex>& vertices, std::vector<Vector3>& tris) : vertexShader(vertexShader), pixelShader(pixelShader)
{
	for (auto vertex : vertices) 
	{
		auto pos = vertex.pos;

		points.push_back({pos.x, pos.y, pos.z, 1});
		points.push_back(vertex.color);
	}

	for (auto t : tris)
	{
		indexes.push_back(t.x);
		indexes.push_back(t.y);
		indexes.push_back(t.z);
	}

	points.shrink_to_fit();
	indexes.shrink_to_fit();

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
		layout.GetAddressOf()
	);

	D3D11_BUFFER_DESC vertexBufDesc = {
		.ByteWidth = static_cast<UINT>(sizeof(DirectX::XMFLOAT4) * points.size()),
		.Usage = D3D11_USAGE_DEFAULT,
		.BindFlags = D3D11_BIND_VERTEX_BUFFER,
		.CPUAccessFlags = 0,
		.MiscFlags = 0,
		.StructureByteStride = 0
	};

	D3D11_SUBRESOURCE_DATA vertexData = {
		.pSysMem = &points[0],
		.SysMemPitch = 0,
		.SysMemSlicePitch = 0
	};

	game.Render.Device->CreateBuffer(&vertexBufDesc, &vertexData, vertexBuffer.GetAddressOf());

	//Index buffer
	D3D11_BUFFER_DESC indexBufDesc = {
		.ByteWidth = static_cast<UINT>(sizeof(int) * indexes.size()),
		.Usage = D3D11_USAGE_DEFAULT,
		.BindFlags = D3D11_BIND_INDEX_BUFFER,
		.CPUAccessFlags = 0,
		.MiscFlags = 0,
		.StructureByteStride = 0
	};

	D3D11_SUBRESOURCE_DATA indexData = {
		.pSysMem = &indexes[0],
		.SysMemPitch = 0,
		.SysMemSlicePitch = 0
	};

	game.Render.Device->CreateBuffer(&indexBufDesc, &indexData, indexBuffer.GetAddressOf());
}