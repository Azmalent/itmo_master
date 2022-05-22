#pragma once

#include "transform.h"
#include "window.h"

#include <d3d.h>
#include <d3d11.h>
#include <SimpleMath.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

struct Camera
{
	friend class Window;

	XMFLOAT3 Position = { 0, 0, -4 };
	XMFLOAT3 Target = { 0, 0, 0 };
	XMFLOAT3 UpVector = { 0, 1, 0 };

	XMMATRIX ViewMatrix;
	XMMATRIX ProjectionMatrix;

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 pos);
	
	void SetTarget(float x, float y, float z);
	void SetTarget(Vector3 target);

	void SetUpVector(float x, float y, float z);
	void SetUpVector(Vector3 up);

	Camera(Window& window);

	void DisableLens();
	void SetLens(float fovY, float zNear, float zFar); //TODO: update when window is resized

	XMFLOAT4X4 GetWorldViewProjectionMatrix(Transform& transform);

private:
	Window& window;

	float fovY;
	float zNear;
	float zFar;

	float nearWindowHeight;
	float farWindowHeight;

	void UpdateViewMatrix();
	void UpdateProjectionMatrix();
};