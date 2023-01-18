#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"

class Goal
{
public:
	void Initialize(float y);

	void Update(WorldTransform worldTransform);

	void Draw(ViewProjection& viewProjection);
	// ���W��n���p
	WorldTransform GetWorldTransform() const { return worldTransform_; }
private:
	// ���f��
	Model* goalModel_ = nullptr;
	// ���W
	WorldTransform worldTransform_;
	DebugText* debugText_;
};

