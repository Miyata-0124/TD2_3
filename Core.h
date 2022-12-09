#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
class Core
{
public:
	void Initialize(float y);
	void Update();
	void Draw(ViewProjection& viewProjection);
private:
	// テクスチャ
	uint32_t textureHandle_ = 0;
	// モデル
	Model* coreModel_ = nullptr;
	// 座標
	WorldTransform worldTransform_;
};

