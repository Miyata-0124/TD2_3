﻿#include "GameScene.h"
#include "TextureManager.h"
#include "Affine.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
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
	if (input_->PushKey(DIK_UP)) {
		if (viewProjection_.eye.y < 50)
		{
			viewProjection_.eye.y += 2.5f;
		}
	}
	else {
		viewProjection_.eye = { 20.0f,20.0f,-30.0f };
		viewProjection_.target = { 0, 0, 0 };
	}
	if (input_->PushKey(DIK_LEFT)) {
		viewProjection_.eye = { -50, 0, 0 };
	}
	if (input_->PushKey(DIK_DOWN)) {
		viewProjection_.eye = { 0, -50, -0.01 };
	}
	if (input_->PushKey(DIK_RIGHT)) {
		viewProjection_.eye = { 50, 0, 0 };
	}
	viewProjection_.UpdateMatrix();
	const float radian = 2.0f;

	//箱の回転
	if (player_->GetWorldTransform().translation_.x > worldTransform_.scale_.x) {
		worldTransform_.rotation_ = { 0.0f, 0.0f, PI / radian };
		Affine::CreateMatRotZ(worldTransform_, worldTransform_.rotation_);
	}
	else if (player_->GetWorldTransform().translation_.x < -worldTransform_.scale_.x) {
		worldTransform_.rotation_ = { 0.0f, 0.0f, -PI / radian };
		Affine::CreateMatRotZ(worldTransform_, worldTransform_.rotation_);
	}
	else if (player_->GetWorldTransform().translation_.z > worldTransform_.scale_.z) {
		worldTransform_.rotation_ = { -PI / radian, 0.0f, 0.0f };
		Affine::CreateMatRotX(worldTransform_, worldTransform_.rotation_);
	}
	else if (player_->GetWorldTransform().translation_.z < -worldTransform_.scale_.z) {
		worldTransform_.rotation_ = { PI / radian, 0.0f, 0.0f };
		Affine::CreateMatRotX(worldTransform_, worldTransform_.rotation_);
	}
	player_->CheckRotate(worldTransform_.scale_.x, worldTransform_.scale_.z);
	player_->Update();

	core_->Update();


	//一周したら0に戻す
	if (worldTransform_.rotation_.x >= PI * 2 || worldTransform_.rotation_.x <= -PI * 2) {
		worldTransform_.rotation_.x = 0.0f;
	}

	if (worldTransform_.rotation_.z >= PI * 2 || worldTransform_.rotation_.z <= -PI * 2) {
		worldTransform_.rotation_.z = 0.0f;
	}

	worldTransform_.TransferMatrix();

	debugCamera_->Update();

	debugText_->SetPos(20, 20);
	debugText_->Printf("%f,%f,%f",
		worldTransform_.rotation_.x,
		worldTransform_.rotation_.y,
		worldTransform_.rotation_.z);
	debugText_->SetPos(20, 40);
	debugText_->Printf("%f,%f,%f",
		player_->GetWorldTransform().translation_.x,
		player_->GetWorldTransform().translation_.y,
		player_->GetWorldTransform().translation_.z);

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
	core_->Draw(viewProjection_);

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