#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
class Core
{
public:
	void Initialize(float y);
	void Update(WorldTransform worldTransform,int rotX,int rotZ);
	void Draw(ViewProjection* viewProjection);
	void CheckRotate(float scale_x, float scale_z);
	// 座標を渡す用
	WorldTransform GetWorldTransform() const{ return worldTransform_; }

	//void SetWorldTransZ(WorldTransform worldTransform);
	//void SetWorldTransX(WorldTransform worldTransform);

private:
	// テクスチャ
	uint32_t textureHandle_ = 0;
	// モデル
	Model* coreModel_ = nullptr;
	// 座標
	WorldTransform worldTransform_;
};

