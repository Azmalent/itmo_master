#pragma once

#include "window.h"

#include <d3d.h>
#include <d3d11.h>
#include <wrl.h>

class RenderDevice
{
	friend class Component;

private:
	ID3D11Texture2D* backBuffer;
	ID3D11RenderTargetView* renderView;
	IDXGISwapChain* swapChain;
	ID3D11RasterizerState* rastState;
	D3D11_VIEWPORT viewport;

public:
	ID3D11Device* Device;
	ID3D11DeviceContext* Context;

	float clearColor[4] = { 0.35f, 0.35f, 0.35f, 1.0f };

	RenderDevice(Window& window);
	void PreDraw();
	void PostDraw(float totalTime);
};