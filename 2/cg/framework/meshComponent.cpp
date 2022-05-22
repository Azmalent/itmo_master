#include "pch.h"

#include <wrl.h>

MeshComponent::MeshComponent(Game& game, Mesh* mesh) : GameComponent(game), mesh(mesh)
{

}

void MeshComponent::Draw()
{
	auto context = game.Render.Context;

	context->IASetInputLayout(mesh->layout.Get());
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->IASetIndexBuffer(mesh->indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, mesh->vertexBuffer.GetAddressOf(), mesh->strides, mesh->offsets);

	context->PSSetShader(mesh->pixelShader->shader.Get(), nullptr, 0);
	context->VSSetShader(mesh->vertexShader->shader.Get(), nullptr, 0);

	auto pixelConstBuffer = mesh->pixelShader->constBuffer;
	if (pixelConstBuffer != nullptr)
	{
		context->PSSetConstantBuffers(0, 1, pixelConstBuffer.GetAddressOf());
		mesh->pixelShader->UpdateConstBuffer(game.Render.Context);
	}

	if (mesh->vertexShader->constBuffer != nullptr)
	{
		context->VSSetConstantBuffers(0, 1, mesh->vertexShader->constBuffer.GetAddressOf());
		mesh->vertexShader->UpdateConstBuffer(game.Render.Context);
	}

	context->DrawIndexed(mesh->indexesSize, 0, 0);
}