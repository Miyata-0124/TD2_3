#pragma once
#include "GameObject3D.h"
#include "MathFunc.h"

class Core
{
public:
	void Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection);
  
	void Update();

	void Draw();
	// 座標を渡す用
	Vector3 GetVelocity()const { return velocity_; }
private:
	//速度用
	Vector3 velocity_ = { 0.0f,0.0f,0.0f };
	//回転用
	Vector3 rot_ = { 0.0f,0.0f,0.0f };
	
	GameObject3D* core = nullptr;
};

