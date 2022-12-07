#include "GameScene.h"
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

	/*textureHandle_ = TextureManager::Load("Box.png");*/
	model_ = Model::CreateFromOBJ("Box",true);
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 5.0f,5.0f,5.0f };
	/*viewProjection_.eye = { 0, 0, -50 };*/
	/*viewProjection_.target = { 0, 0, 0 };*/
	viewProjection_.Initialize();
	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();
}

void GameScene::Update() {
	const float kEyeSpeed = 0.2f;
	if (input_->PushKey(DIK_UP)) {
		viewProjection_.eye = { 0, 50, -0.1 ,};
	}
	else {
		viewProjection_.eye = { 0, 0, -50 };
		viewProjection_.target = { 0, 0, 0 };
	}
	if (input_->PushKey(DIK_LEFT)) {
		viewProjection_.eye = { -50, 0, 0 };
	}
	if (input_->PushKey(DIK_DOWN)) {
		viewProjection_.eye = { 0, -50, -0.1 };
	}
	if (input_->PushKey(DIK_RIGHT)) {
		viewProjection_.eye = { 50, 0, 0 };
	}
	if (input_->PushKey(DIK_W)) {
		worldTransform_.rotation_ += {3.14f / 8.0f, 0.0f, 0.0f};
		Affine::CreateAffine(worldTransform_);
	}
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_ -= {0.0f, 3.14f / 8.0f, 0.0f};
		Affine::CreateAffine(worldTransform_);
	}
	if (input_->PushKey(DIK_S)) {
		worldTransform_.rotation_ -= {3.14f / 8.0f, 0.0f, 0.0f};
		Affine::CreateAffine(worldTransform_);
	}
	if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_ += {0.0f, 3.14f / 8.0f, 0.0f};
		Affine::CreateAffine(worldTransform_);
	}
	worldTransform_.TransferMatrix();
	viewProjection_.UpdateMatrix();
	debugCamera_->Update();
	//デバッグ用表示
	/*debugText_->SetPos(50, 50);
	debugText_->Printf("eye:(%f,%f, %f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
	debugText_->SetPos(50, 70);
	debugText_->Printf("target:(%f,%f, %f)", viewProjection_.target.x, viewProjection_.target.y, viewProjection_.target.z);*/
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
