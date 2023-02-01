#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Object3d.h"
class Core
{
public:
	~Core();

	void Initialize(float y);

	void Update(Object3d* obj,bool *collision);

	void Draw();

	void SetIsFall(bool fall) { isFall = fall; }

	void Rotate(Object3d* obj);
	// 座標を渡す用
	Object3d* GetTransform() { return coreObject_; }
	Vector3 GetVelocity()const { return velocity_; }
	/*void SetWorldTransform(WorldTransform worldTransform);*/

private:
	static const int leadNum = 30;
	//速度用
	Vector3 velocity_ = { 0.0f,0.0f,0.0f };
	// モデル
	Model* coreModel_ = nullptr;
	// 座標
	Object3d* coreObject_ = nullptr;
	/*WorldTransform worldTransform_;
	WorldTransform leadWorldTransformsX_[leadNum];
	WorldTransform leadWorldTransformsY_[leadNum];
	WorldTransform leadWorldTransformsZ_[leadNum];*/
	bool isFall = 0;
};
