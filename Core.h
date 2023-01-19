#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
// #include "DebugText.h"
#include "GameObject3D.h"

class Core
{
public:
	void Initialize(float y);
  
	void Update(WorldTransform worldTransform);

	void Draw(ViewProjection* viewProjection);
	// 座標を渡す用
	WorldTransform GetWorldTransform() const{ return worldTransform_; }
	Vector3 GetVelocity()const { return velocity_; }

	void SetWorldTransform(WorldTransform worldTransform);
private:
	//速度用
	Vector3 velocity_ = { 0.0f,0.0f,0.0f };
	//回転用
	Vector3 rot_ = { 0.0f,0.0f,0.0f };
	// テクスチャ
	uint32_t textureHandle_ = 0;
	// モデル
	Model* coreModel_ = nullptr;
	GameObject3D* coreObject_ = nullptr;
	// 座標
	WorldTransform worldTransform_;
	//DebugText* debugText_;
};

