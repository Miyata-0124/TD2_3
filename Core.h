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
	// �e�N�X�`��
	uint32_t textureHandle_ = 0;
	// ���f��
	Model* coreModel_ = nullptr;
	// ���W
	WorldTransform worldTransform_;
};

