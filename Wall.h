#pragma once
#include "Input.h"
#include "map.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "GameObject3D.h"

class Wall
{
public:
	~Wall();

	void Initialize();

	void SetBlock();

	void Rotate(WorldTransform worldTransform);

	void Draw(ViewProjection* viewProjection);

	WorldTransform* GetWorldTransform();

private:

	Model* wallModel_ = nullptr;
	GameObject3D* wallObject_ = nullptr;
	ViewProjection viewProjection_;
	WorldTransform worldTransform_[totalBlockNum];

	int top[9][9] = {
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
};

