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
	// ���W��n���p
	WorldTransform GetWorldTransform() const{ return worldTransform_; }

	void SetWorldTransform(WorldTransform worldTransform);
private:
	Vector3 velocity_ = { 0.0f,0.0f,0.0f };
	// �e�N�X�`��
	uint32_t textureHandle_ = 0;
	// ���f��
	Model* coreModel_ = nullptr;
	// ���W
	WorldTransform worldTransform_;
	DebugText* debugText_;
};

