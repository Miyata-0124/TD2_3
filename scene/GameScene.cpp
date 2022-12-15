#include "GameScene.h"
#include "TextureManager.h"
#include "Affine.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamera_;
	delete core_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	model_ = Model::CreateFromOBJ("Box", true);
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 7.0f,7.0f,7.0f };
  	worldTransform_.translation_ = { 0.0f,0.0f,0.0f };

	//プレイヤーの生成
	player_ = new Player();
	player_->Initialize(worldTransform_.scale_.y);

	//コアの生成
	core_ = new Core();
	core_->Initialize(worldTransform_.scale_.y);

	viewProjection_.Initialize();
	viewProjection_.eye = { 20.0f,20.0f,-30.0f };
	viewProjection_.UpdateMatrix();
	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();
}

void GameScene::Update() {

	const float radian = PI / 100.0f;

	//箱の回転
	if (player_->GetWorldTransform().translation_.x > worldTransform_.scale_.x) {
		worldTransform_.rotation_ = {0.0f, 0.0f, radian};
		isRotateZ = 1;
	}
	else if (player_->GetWorldTransform().translation_.x < -worldTransform_.scale_.x) {
		worldTransform_.rotation_ = { 0.0f, 0.0f, -radian };
		isRotateZ = 1;
	}
	else if (player_->GetWorldTransform().translation_.z > worldTransform_.scale_.z) {
		worldTransform_.rotation_ = { -radian, 0.0f, 0.0f };
		isRotateX = 1;
	}
	else if (player_->GetWorldTransform().translation_.z < -worldTransform_.scale_.z) {
		worldTransform_.rotation_ = { radian, 0.0f, 0.0f };
		isRotateX = 1;
	}

	//ステージ回転時、プレイヤーも一緒に回転する
	player_->SetWorldTransform(worldTransform_);
	
	//回転中
	if (isRotateZ) {
		Affine::CreateMatRotZ(worldTransform_, worldTransform_.rotation_);
		core_->SetWorldTransform(worldTransform_);
	}
	else if (isRotateX) {
		Affine::CreateMatRotX(worldTransform_, worldTransform_.rotation_);
		core_->SetWorldTransform(worldTransform_);
	}
	//回転後
	else {
		player_->Update();
		core_->Update(worldTransform_);
	}

	if (isRotateX || isRotateZ) {
		rotateTimer += radian;

		if (rotateTimer >= PI / 2) {
			isRotateZ = 0;
			isRotateX = 0;
			rotateTimer = 0;
		}
	}
  
	//一周したら0に戻す
	if (worldTransform_.rotation_.x >= PI * 2 || worldTransform_.rotation_.x <= -PI * 2) {
		worldTransform_.rotation_.x = 0.0f;
	}

	if (worldTransform_.rotation_.z >= PI * 2 || worldTransform_.rotation_.z <= -PI * 2) {
		worldTransform_.rotation_.z = 0.0f;
	}

	worldTransform_.TransferMatrix();

	debugCamera_->Update();
	//Box
	debugText_->SetPos(20, 20);
	debugText_->Printf("Box:%f,%f,%f",
		worldTransform_.rotation_.x,
		worldTransform_.rotation_.y,
		worldTransform_.rotation_.z
	);

	//player
	debugText_->SetPos(350, 20);
	debugText_->Printf("Player:%f,%f,%f",
		player_->GetWorldTransform().translation_.x,
		player_->GetWorldTransform().translation_.y,
		player_->GetWorldTransform().translation_.z
	);
	//Core
	debugText_->SetPos(680, 20);
	debugText_->Printf("CoreRot:%f,%f,%f",
		core_->GetWorldTransform().rotation_.x,
		core_->GetWorldTransform().rotation_.y,
		core_->GetWorldTransform().rotation_.z
	);
	debugText_->SetPos(680, 40);
	debugText_->Printf("CoreTrans%f,%f,%f",
		core_->GetWorldTransform().matWorld_.m[3][0],
		core_->GetWorldTransform().matWorld_.m[3][1],
		core_->GetWorldTransform().matWorld_.m[3][2]
	);
	debugText_->SetPos(680, 60);
	debugText_->Printf("Velocity_:%f,%f,%f",
		core_->GetVelocity().x,
		core_->GetVelocity().y,
		core_->GetVelocity().z
	);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldTransform_, viewProjection_);
	player_->Draw(&viewProjection_);
	core_->Draw(&viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}