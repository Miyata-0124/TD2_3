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
	// 座標を渡す用
	WorldTransform GetWorldTransform() const { return worldTransform_; }
private:
	// モデル
	Model* goalModel_ = nullptr;
	// 座標
	WorldTransform worldTransform_;
	DebugText* debugText_;
};

