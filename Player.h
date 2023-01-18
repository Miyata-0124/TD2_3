#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "GameObject3D.h"

class Player
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	void Initialize(float y);

	void Update(WorldTransform* worldTransform, bool* collision);

	void Draw(ViewProjection* viewProjection);

	void CheckRotate(float scale_x, float scale_z);

	WorldTransform GetWorldTransform();

	void Rotate(WorldTransform worldTransform);

private:
	Input* input_ = nullptr;
	uint32_t textureHandle_ = 0;

	Model* playerModel_ = nullptr;
	GameObject3D* playerObject_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	float speed = 0.2f;

};

