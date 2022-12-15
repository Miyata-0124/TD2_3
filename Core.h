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
	// ���W��n���p
	WorldTransform GetWorldTransform() const{ return worldTransform_; }

	//void SetWorldTransZ(WorldTransform worldTransform);
	//void SetWorldTransX(WorldTransform worldTransform);

private:
	// �e�N�X�`��
	uint32_t textureHandle_ = 0;
	// ���f��
	Model* coreModel_ = nullptr;
	// ���W
	WorldTransform worldTransform_;
};

