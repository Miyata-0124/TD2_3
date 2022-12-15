#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"

class Core
{
public:
	void Initialize(float y);
	void Update(WorldTransform worldTransform);
	void Draw(ViewProjection* viewProjection);
	void CheckRotate(float scale_x, float scale_z);
	// 座標を渡す用
	WorldTransform GetWorldTransform() const{ return worldTransform_; }

	void SetWorldTransform(WorldTransform worldTransform);
private:
	Vector3 velocity_ = { 0.0f,0.0f,0.0f };
	// テクスチャ
	uint32_t textureHandle_ = 0;
	// モデル
	Model* coreModel_ = nullptr;
	// 座標
	WorldTransform worldTransform_;
	DebugText* debugText_;
};

