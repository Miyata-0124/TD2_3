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

	void Update(Input* input, Object3d* obj, bool* collision);

	void Draw();

	void CheckRotate(float scale_x, float scale_z);

	XMFLOAT3 GetPosition() { return playerObject_->position; }
	Object3d* GetTransform() { return playerObject_; }
	XMFLOAT3 GetScale() { return playerObject_->scale; }

	//WorldTransform GetWorldTransform();

	void Rotate(Object3d* obj);
	//void SetRotation(const Vector3& rotation) { playerObject_->rotation = rotation; }

private:
	//Input* input_ = nullptr;
	//uint32_t textureHandle_ = 0;

	Model* playerModel_ = Model::LoadFromOBJ("triangle_mat");
	Object3d* playerObject_ = Object3d::Create();
	//WorldTransform worldTransform_;
	//ViewProjection viewProjection_;

	const float MAX_SPEED = 0.2f;
	float speedX = 0.0f;
	float speedZ = 0.0f;

	float scale = 0.0f;
	float scaleVal = 0.01f;

};