#pragma once

#include "game.h"

#include <d3dcompiler.h>

struct ShaderBase
{
protected:
	ShaderBase(Game& game, LPCWSTR filename, LPCSTR target, const D3D_SHADER_MACRO* macros, ID3DInclude* include);
	Game& game;

public:
	ID3DBlob* byteCode;
};

struct VertexShader : public ShaderBase
{
public:
	VertexShader(Game& game, LPCWSTR filename, const D3D_SHADER_MACRO* macros, ID3DInclude* include);
	ID3D11VertexShader* shader;
};

struct PixelShader : public ShaderBase
{
public:
	PixelShader(Game& game, LPCWSTR filename, const D3D_SHADER_MACRO* macros, ID3DInclude* include);
	ID3D11PixelShader* shader;
};