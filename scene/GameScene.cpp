﻿#include "GameScene.h"
#include "TextureManager.h"
#include "Affine.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	model_ = Model::CreateFromOBJ("Box",true);
	worldTransformPearent_.Initialize();
	worldTransformPearent_.scale_ = { 5.0f,5.0f,5.0f };

	worldTransform_.Initialize();
	worldTransform_.scale_ = { 0.5f,0.5f,0.5f };
	worldTransform_.translation_ = { 0.0f,1.2f,0.0f };
	worldTransform_.parent_ = &worldTransformPearent_;

	viewProjection_.Initialize();

	Affine::CreateAffine(worldTransformPearent_, face);
	Affine::CreateAffine(worldTransform_, face);
	worldTransformPearent_.TransferMatrix();
	worldTransform_.TransferMatrix();
}

void GameScene::Update() {
	const float radian = 8.0f;

	if (input_->TriggerKey(DIK_A)) {
		worldTransformPearent_.rotation_ = {0.0f, 0.0f, PI / radian};
		Affine::CreateMatRotZ(worldTransformPearent_, worldTransformPearent_.rotation_);

	}
	if (input_->TriggerKey(DIK_D)) {
		worldTransformPearent_.rotation_ = {0.0f, 0.0f, -PI / radian};
		Affine::CreateMatRotZ(worldTransformPearent_, worldTransformPearent_.rotation_);
		//Affine::CreateAffineZ(worldTransformPearent_);
		
	}
	
	if (input_->TriggerKey(DIK_W)) {
		worldTransformPearent_.rotation_ = {PI / radian, 0.0f, 0.0f};
		Affine::CreateMatRotX(worldTransformPearent_, worldTransformPearent_.rotation_);
		//Affine::CreateAffineX(worldTransformPearent_);
	}
	if (input_->TriggerKey(DIK_S)) {
		worldTransformPearent_.rotation_ = {-PI / radian, 0.0f, 0.0f};
		Affine::CreateMatRotX(worldTransformPearent_, worldTransformPearent_.rotation_);
		//Affine::CreateAffineX(worldTransformPearent_);
	}

	if (input_->TriggerKey(DIK_Q)) {
		worldTransformPearent_.rotation_ += {0.0f, PI / radian, 0.0f};
		//Affine::CreateAffineZ(worldTransformPearent_);

	}
	if (input_->TriggerKey(DIK_E)) {
		worldTransformPearent_.rotation_ -= {0.0f, PI / radian, 0.0f};
		//Affine::CreateAffineZ(worldTransformPearent_);

	}
	
	if (worldTransformPearent_.rotation_.x >= PI * 2 || worldTransformPearent_.rotation_.x <= -PI * 2) {
		worldTransformPearent_.rotation_.x = 0.0f;
	}

	if (worldTransformPearent_.rotation_.z >= PI * 2 || worldTransformPearent_.rotation_.z <= -PI * 2) {
		worldTransformPearent_.rotation_.z = 0.0f;
	}

	if (input_->TriggerKey(DIK_SPACE)) {
		if (face == 0) {
			face = 1;
		}
		else {
			face = 0;
		}
	}
	////実移動
	//worldTransform_.translation_ = {
	//	-sin(PI * radianX) * 10.0f,
	//	-cos(PI * radianY) * 10.0f,
	//	-cos(PI * radianZ) * 1.0f,
	//};

	////移動に合わせて回転
	//worldTransform_.rotation_ = {
	//	0.0f,
	//	radian * PI,
	//	0.0f,
	//};

	/*if (worldTransformPearent_.rotation_.z != 0.0f && worldTransform_.translation_.x < 1.5f) {
		worldTransform_.translation_.x += 0.1f;
	}
	if (worldTransformPearent_.rotation_.x != 0.0f && worldTransform_.translation_.z > -1.5f) {
		worldTransform_.translation_.z -= 0.1f;
	}*/

	if (input_->TriggerKey(DIK_X)) {
		worldTransform_.translation_.y -= 0.1f;
	}
	if (worldTransform_.translation_.y < 1.2f && worldTransform_.translation_.y >= -1.2f) {
		worldTransform_.translation_.y -= 0.1f;
	}

	//Affine::CreateAffine(worldTransformPearent_, face);
	worldTransformPearent_.TransferMatrix();
	//worldTransformPearent_.TransferMatrix();

	Affine::CreateAffine(worldTransform_, face);
	worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	worldTransform_.TransferMatrix();

	debugCamera_->Update();

	debugText_->SetPos(20, 20);
	debugText_->Printf("%f,%f,%f",
		worldTransformPearent_.rotation_.x,
		worldTransformPearent_.rotation_.y,
		worldTransformPearent_.rotation_.z);

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
	model_->Draw(worldTransformPearent_, debugCamera_->GetViewProjection());
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection());

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
