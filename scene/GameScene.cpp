#include "GameScene.h"
#include "TextureManager.h"
#include "Affine.h"
#include <cassert>
#include <MathUtility.h>
using namespace MathUtility;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete coreModel_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	//Core
	textureHandle_ = TextureManager::Load("Core.png");
	coreModel_ = Model::Create();
	coreTransform_.Initialize();
	coreTransform_.scale_ = { 0.5f,0.5f,0.5f };
	coreTransform_.translation_ = { 0.0f,5.5f,0.0f };
	//Box
	model_ = Model::CreateFromOBJ("Box", true);
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 5.0f,5.0f,5.0f };

	viewProjection_.Initialize();
	Affine::CreateAffine(worldTransform_);
	Affine::CreateAffine(coreTransform_);
	worldTransform_.TransferMatrix();
	coreTransform_.TransferMatrix();
}

void GameScene::Update() {
	if (input_->TriggerKey(DIK_W)) {
		worldTransform_.rotation_ += {-(3.14f / 2.0f), 0.0f, 0.0f};
	}
	if (input_->TriggerKey(DIK_A)) {
		worldTransform_.rotation_ += {0.0f, -(3.14f / 2.0f), 0.0f};
	}
	if (input_->TriggerKey(DIK_S)) {
		worldTransform_.rotation_ += {3.14f / 2.0f, 0.0f, 0.0f};
	}
	if (input_->TriggerKey(DIK_D)) {
		worldTransform_.rotation_ += { 0.0f, 3.14f / 2.0f, 0.0f};
	}
	Affine::CreateAffine(worldTransform_);
	Affine::CreateAffine(coreTransform_);
	worldTransform_.TransferMatrix();
	coreTransform_.TransferMatrix();
	debugCamera_->Update();
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
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection());
	coreModel_->Draw(coreTransform_, debugCamera_->GetViewProjection(),textureHandle_);
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
