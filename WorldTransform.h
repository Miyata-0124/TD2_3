﻿#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include "MathFunc.h"

class WorldTransform {
public:
	//メンバ関数
	void Initialize();

	//ワールド変換行列の更新
	void UpdateMatWorld();

	//メンバ変数
	//スケール
	Vector3 scale_;
	//XYZ軸回転
	Vector3 rotation_;
	//ローカル座標
	Vector3 translation_;
	//ワールド変換行列
	Matrix4 matWorld_;
	//親オブジェクトのワールド変換のポインタ
	WorldTransform* parent = nullptr;

};

