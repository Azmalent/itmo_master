#pragma once

#include "window.h"

#include <d3d.h>
#include <d3d11.h>
#include <wrl.h>

using namespace Microsoft::WRL;

class RenderDevice
{
	friend class Component;

private:
	ComPtr<ID3D11Texture2D> backBuffer;
	ComPtr<ID3D11RenderTargetView> renderView;
	ComPtr<IDXGISwapChain> swapChain;
	ComPtr<ID3D11RasterizerState> rastState;
	D3D11_VIEWPORT viewport;

public:
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> Context;

	float clearColor[4] = { 0.35f, 0.35f, 0.35f, 1.0f };
	void SetClearColor(float r, float g, float b);

	RenderDevice(Window& window);
	void PreDraw();
	void PostDraw(float totalTime);
};