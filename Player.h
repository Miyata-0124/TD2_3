#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Object3d.h"

class Player
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	void Initialize(float y);

	void Update(Input* input);

	void Draw();

	void CheckRotate(float scale_x, float scale_z);

	XMFLOAT3 GetPosition() { return playerObject_->position; }

	//WorldTransform GetWorldTransform();

	void Rotate(Object3d* obj);
	//void SetRotation(const Vector3& rotation) { playerObject_->rotation = rotation; }

private:
	//Input* input_ = nullptr;
	//uint32_t textureHandle_ = 0;

	Model* playerModel_ = nullptr;
	Object3d* playerObject_ = nullptr;
	//WorldTransform worldTransform_;
	//ViewProjection viewProjection_;

	float speed = 0.2f;

};

