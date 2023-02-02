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

	void SetStageNum(int num) { stageNum = num; }

	int GetStageNum() { return stageNum; }
	XMFLOAT3* GetPosition() { return &wallObject->position; }
	XMFLOAT3 GetScale() { return wallObject->scale; }
	Object3d* GetTransform() { return wallObject; }

private:

	Model* model_ = Model::LoadFromOBJ("woodCube");
	Object3d wallObject[totalBlockNum];

	float stageSize = 11.0f;
	int stageNum = 1;
};
