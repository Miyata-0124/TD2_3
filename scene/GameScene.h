#pragma once
#include "Audio.h"
#include "DX12base.h"
#include "DebugText.h"
//include "DebugCamera.h"
#include "Input.h"
#include "Model.h"
//include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "map.h"
// 作成したクラス
#include "Player.h"
#include "Core.h"
#include "Wall.h"
//include "Goal.h"



class GameScene {

public: // メンバ関数

	//コンストラクタ
	GameScene();

	/// デストラクタ
	~GameScene();

	//初期化
	void Initialize(WinApp* winApp);

	//毎フレーム処理
	void Update();

	//描画処理
	void Draw();

	void Reset();
	//当たり判定
	bool CheakCollision(Vector3 posA, Vector3 posB, Vector3 sclA, Vector3 sclB);

private: // メンバ変数
	Audio audio_;
	DX12base* dx12base_ = nullptr;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	const float PI = 3.14159f;

	Model* stageModel_ = nullptr;
	GameObject3D* stageObject_ = nullptr;
	//WorldTransform worldTransformPearent_;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	//DebugCamera* debugCamera_ = nullptr;

	Player* player_ = nullptr;
	Core* core_ = nullptr;
	Wall* wall_ = nullptr;
	//Goal* goal_ = nullptr;

	int isRotateZ = 0;
	int isRotateX = 0;
	float rotateTimer = 0.0f;

	Vector3 wallCollisions[totalBlockNum];
	bool isHit[totalBlockNum] = { 0 };
private: // メンバ変数
	WinApp* winApp_ = nullptr;
	XMMATRIX matProjection_ = {};
	Audio soundManager_;

	//音声読み込み
	//SoundData soundData1 = soundManager_.SoundLoadWave("Resources/Alarm01.wav");


	//シーン管理
	enum class Scene
	{
		Title,  //タイトル
		//Select, //ステージセレクト
		Stage,  //ステージ
		Clear,  //クリア
		Over,   //オーバー
	};

	Scene scene_ = Scene::Title;

	int stage = 0;

	const float radian = PI / 100.0f;

	Vector3 playerCollision = {
			player_->GetWorldTransform().matWorld_.m[3][0],
			player_->GetWorldTransform().matWorld_.m[3][1],
			player_->GetWorldTransform().matWorld_.m[3][2],
	};
};