#pragma once

#include "game.h"
#include "components/object.h"

#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <wrl.h>

using namespace DirectX;
using namespace Microsoft::WRL;

struct ShaderBase
{
protected:
	ShaderBase(Game& game, LPCWSTR filename, LPCSTR target, const D3D_SHADER_MACRO* macros, ID3DInclude* include, void* constBuf, UINT constBufSize);
	Game& game;

public:
	ComPtr<ID3DBlob> byteCode;
	ComPtr<ID3D11Buffer> constBuffer;
};

struct BaseVertexConstBuffer
{
	XMFLOAT4X4 WorldViewProjection;
	float Time;

	BaseVertexConstBuffer(Transform transform, float time)
	{
		WorldViewProjection = transform.GetWorldViewProjection();
		Time = time;
	}
};

struct VertexShader : public ShaderBase
{
public:
	VertexShader(Game& game, LPCWSTR filename, const D3D_SHADER_MACRO* macros, ID3DInclude* include, void* constBuf, UINT constBufSize);
	ComPtr<ID3D11VertexShader> shader;
};

struct BasePixelConstBuffer
{
	float Time;
	BasePixelConstBuffer(float time) : Time(time) { }
};

struct PixelShader : public ShaderBase
{
public:
	PixelShader(Game& game, LPCWSTR filename, const D3D_SHADER_MACRO* macros, ID3DInclude* include, void* constBuf, UINT constBufSize);
	ComPtr<ID3D11PixelShader> shader;
};