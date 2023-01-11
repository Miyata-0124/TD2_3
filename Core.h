#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"

class Core
{
public:
	void Initialize(float y);
  
	void Update(WorldTransform worldTransform, WorldTransform* wall, bool* collision);

	void Draw(ViewProjection* viewProjection);
	// 座標を渡す用
	WorldTransform GetWorldTransform() const{ return worldTransform_; }
	Vector3 GetVelocity()const { return velocity_; }

	void SetWorldTransform(WorldTransform worldTransform);
	void SetIsFall(bool fall) {  isFall = fall; }
private:
	//速度用
	Vector3 velocity_ = { 0.0f,0.0f,0.0f };
	// テクスチャ
	uint32_t textureHandle_ = 0;
	// モデル
	Model* coreModel_ = nullptr;
	// 座標
	WorldTransform worldTransform_;
	DebugText* debugText_;

	bool isFall = 0;
};

