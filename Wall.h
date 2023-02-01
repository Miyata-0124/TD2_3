#pragma once
#include "Input.h"
#include "map.h"
#include "Object3d.h"

class Wall
{
public:
	~Wall();

	void Initialize();

	void SetBlock();

	void Rotate(Object3d* obj);

	void Draw();

	XMFLOAT3* GetPosition() { return &wallObject->position; }
	XMFLOAT3 GetScale() { return wallObject->scale; }
	Object3d* GetTransform() { return wallObject; }

private:

	Model* model_ = nullptr;
	Object3d wallObject[totalBlockNum];

	int face[mapWidth][mapHeight] = {
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
	};

	float stageSize = 11.0f;
};
