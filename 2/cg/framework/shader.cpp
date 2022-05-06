#include "pch.h"

#include <iostream>

ShaderBase::ShaderBase(Game& game, LPCWSTR filename, LPCSTR target, const D3D_SHADER_MACRO* macros, ID3DInclude* include) : game(game)
{
	ComPtr<ID3DBlob> errorCode;

	auto res = D3DCompileFromFile(filename,
		macros,
		include,
		"main",
		target,
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		byteCode.GetAddressOf(),
		errorCode.GetAddressOf());

	if (FAILED(res)) 
	{
		if (errorCode != nullptr) 
		{
			char* compileErrors = (char*)(errorCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		else
		{
			MessageBox(game.Window.hWnd, filename, L"Missing shader file!", MB_OK);
		}

		return;
	}
}

VertexShader::VertexShader(Game& game, LPCWSTR filename, const D3D_SHADER_MACRO* macros, ID3DInclude* include) : ShaderBase(game, filename, "vs_5_0", macros, include)
{
	game.Render.Device->CreateVertexShader(byteCode->GetBufferPointer(), byteCode->GetBufferSize(), nullptr, shader.GetAddressOf());
}

PixelShader::PixelShader(Game& game, LPCWSTR filename, const D3D_SHADER_MACRO* macros, ID3DInclude* include) : ShaderBase(game, filename, "ps_5_0", macros, include)
{
	game.Render.Device->CreatePixelShader(byteCode->GetBufferPointer(), byteCode->GetBufferSize(), nullptr, shader.GetAddressOf());
}