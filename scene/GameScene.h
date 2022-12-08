﻿#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "DebugCamera.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	WorldTransform GetWorldTransform() { return worldTransform_;}

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	const float PI = 3.14159f;
	float radianX = 0.0f;
	float radianY = 0.0f;
	float radianZ = 0.0f;
	 
	int face = 0;
  //Box
	uint32_t textureHandle_ = 0;
	Model* model_ = nullptr;
	WorldTransform worldTransformPearent_;
	WorldTransform worldTransform_;
	//Core
	Model* coreModel_ = nullptr;
	WorldTransform coreTransform_;
	ViewProjection viewProjection_;
	DebugCamera* debugCamera_ = nullptr;
};
