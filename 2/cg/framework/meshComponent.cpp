#include "pch.h"

#include <wrl.h>

MeshComponent::MeshComponent(Game& game, Mesh* mesh) : GameComponent(game), mesh(mesh)
{

}

MeshComponent::~MeshComponent()
{
	delete mesh;
}

void MeshComponent::Draw()
{
	auto context = game.Render.Context;

	context->IASetInputLayout(mesh->layout);
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->IASetIndexBuffer(mesh->indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, &(mesh->vertexBuffer), mesh->strides, mesh->offsets);

	context->PSSetShader(mesh->pixelShader->shader, nullptr, 0);
	context->VSSetShader(mesh->vertexShader->shader, nullptr, 0);

	context->DrawIndexed(mesh->indexesSize, 0, 0);
}