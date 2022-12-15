#pragma once

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
#include "Player.h"
#include "Wall.h"
#include "map.h"

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

	WorldTransform GetWorldTransform() { return worldTransform_; }

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//当たり判定
	bool CheakCollision(Vector3 posA, Vector3 posB, Vector3 sclA, Vector3 sclB);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	const float PI = 3.14159f;

	uint32_t tex = 0;
	Model* model_ = nullptr;
	Model* model2_ = nullptr;
	WorldTransform worldTransform_;
	WorldTransform worldTransform2_;
	ViewProjection viewProjection_;
	DebugCamera* debugCamera_ = nullptr;

	Player* player_ = nullptr;
	Wall* wall_ = nullptr;

	int isRotateZ = 0;
	int isRotateX = 0;
	float rotateTimer = 0.0f;

	Vector3 wallCollisions[totalBlockNum];
	bool isHit[totalBlockNum] = { 0 };

	float a = 0.01f;
};

