#include "pch.h"

Camera::Camera(Window& window) : window(window)
{
	DisableLens();
	UpdateViewMatrix();
}

void Camera::SetPosition(float x, float y, float z)
{
	Position = Vector3(x, y, z);
	UpdateViewMatrix();
}

void Camera::SetPosition(Vector3 pos)
{
	Position = pos;
	UpdateViewMatrix();
}

void Camera::SetTarget(float x, float y, float z)
{
	Target = Vector3(x, y, z);
	UpdateViewMatrix();
}

void Camera::SetTarget(Vector3 target)
{
	Target = target;
	UpdateViewMatrix();
}

void Camera::SetUpVector(float x, float y, float z)
{
	UpVector = Vector3(x, y, z);
	UpdateViewMatrix();
}

void Camera::SetUpVector(Vector3 up)
{
	UpVector = up;
	UpdateViewMatrix();
}

void Camera::DisableLens()
{
	this->fovY = -1;
	this->zNear = -1;
	this->zFar = -1;

	ProjectionMatrix = XMMatrixIdentity();
}

void Camera::SetLens(float fovY, float zNear, float zFar)
{
	this->fovY = fovY;
	this->zNear = zNear;
	this->zFar = zFar;

	nearWindowHeight = 2.0f * zNear * tanf(0.5f * fovY);
	farWindowHeight = 2.0f * zFar * tanf(0.5f * fovY);
	
	UpdateProjectionMatrix();
}

void Camera::UpdateViewMatrix()
{
	XMVECTOR pos = XMLoadFloat3(&Position);
	XMVECTOR target = XMLoadFloat3(&Target);
	XMVECTOR up = XMLoadFloat3(&UpVector);
	ViewMatrix = XMMatrixLookAtLH(pos, target, up);
}

void Camera::UpdateProjectionMatrix()
{
	if (fovY > 0 && zNear > 0 && zFar > 0)
	{
		ProjectionMatrix = XMMatrixPerspectiveFovLH(fovY, window.GetAspectRatio(), zNear, zFar);
	}
}

XMFLOAT4X4 Camera::GetWorldViewProjectionMatrix(Transform& transform)
{
	auto wvpMatrix = transform.GetWorldMatrix() * ViewMatrix * ProjectionMatrix;

	auto transposed = XMMatrixTranspose(wvpMatrix);

	XMFLOAT4X4 result;
	XMStoreFloat4x4(&result, transposed);
	return result;
}