#pragma once

#include "component.h"
#include "../mesh.h"

class MeshComponent : public GameComponent
{
private:
	Mesh* mesh;

public:
	MeshComponent(Game& game, Mesh* mesh);
	~MeshComponent();

	void Draw();
};