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
	XMFLOAT3 GetVelocity()const { return velocity_; }
	/*void SetWorldTransform(WorldTransform worldTransform);*/

private:
	static const int leadNum = 50;
	const float scale = 0.2f;
	//速度用
	XMFLOAT3 velocity_ = { 0.0f,0.0f,0.0f };
	// モデル
	Model* coreModel_ = Model::LoadFromOBJ("core");
	Model* leadModel_ = Model::LoadFromOBJ("Enemy");
	// 座標
	Object3d* coreObject_ = Object3d::Create();

	Object3d leadWorldTransformsX_[leadNum];
	Object3d leadWorldTransformsY_[leadNum];
	Object3d leadWorldTransformsZ_[leadNum];
	bool isFall = 0;
};