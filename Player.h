#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Player
{
public:
	/// <summary>
	/// ƒfƒXƒgƒ‰ƒNƒ^
	/// </summary>
	~Player();

	void Initialize(float y);

	void Update();

	void Draw(ViewProjection *viewProjection);

	void CheckRotate(float scale_x, float scale_z);

	WorldTransform GetWorldTransform();

	void SetWorldTransform(WorldTransform worldTransform);

private:
	Input* input_ = nullptr;
	uint32_t textureHandle_ = 0;

	Model* playerModel_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

};

