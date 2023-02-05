#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Object3d.h"
class Goal
{
public:
	Goal();

	~Goal();

	void Initialize(float y);

	void Update();

	void Draw();

	void Rotate(Object3d* obj);
	// 座標を渡す用
	/*WorldTransform GetWorldTransform() const { return worldTransform_; }*/
	Object3d* GetTransform() { return goalObject_; }
	XMFLOAT3 GetScale() { return goalObject_->scale; }
	Vector3 GetVelocity()const { return velocity_; }
	/*void SetWorldTransform(WorldTransform worldTransform);*/
	void SetIsFall(bool fall) { isFall = fall; }
private:
	static const int leadNum = 30;
	//速度用
	Vector3 velocity_ = { 0.0f,0.0f,0.0f };
	// モデル
	Model* goalModel_ = nullptr;
	// 座標

	Object3d* goalObject_ = nullptr;
	/*WorldTransform worldTransform_;
	WorldTransform leadWorldTransformsX_[leadNum];
	WorldTransform leadWorldTransformsY_[leadNum];
	WorldTransform leadWorldTransformsZ_[leadNum];*/
	bool isFall = 0;
};