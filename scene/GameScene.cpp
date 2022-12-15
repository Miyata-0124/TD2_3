#include "GameScene.h"
#include "TextureManager.h"
#include "Affine.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete model2_;
	delete player_;
	delete wall_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	tex = TextureManager::Load("block.png");

	model_ = Model::CreateFromOBJ("Box", true);
	model2_ = Model::Create();
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 7.0f,7.0f,7.0f };
	worldTransform_.translation_ = { 0.0f,0.0f,0.0f };

	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();

	worldTransform2_.Initialize();
	worldTransform2_.scale_ = { 0.5f,0.5f,0.5f };
	worldTransform2_.translation_ = { 0.0f,8.0f,0.0f };

	Affine::CreateAffine(worldTransform2_);
	worldTransform2_.TransferMatrix();

	//壁ブロックの生成
	wall_ = new Wall();
	wall_->Initialize();

	//プレイヤーの生成
	player_ = new Player();
	player_->Initialize(worldTransform_.scale_.y);

	viewProjection_.Initialize();
	viewProjection_.fovAngleY += a;
	viewProjection_.eye = { 20.0f,40.0f,-40.0f };
	viewProjection_.UpdateMatrix();
}

void GameScene::Update() {
	const float radian = PI / 100.0f;

	if (input_->PushKey(DIK_P)) {
		viewProjection_.fovAngleY += a;
	}
	if (input_->PushKey(DIK_O)) {
		viewProjection_.fovAngleY -= a;
	}
	

	//プレイヤーの位置をとる
	Vector3 playerCollision = {
		player_->GetWorldTransform().matWorld_.m[3][0],
		player_->GetWorldTransform().matWorld_.m[3][1],
		player_->GetWorldTransform().matWorld_.m[3][2],
	};

	for (int i = 0; i < totalBlockNum; i++) {

		//壁ブロックの位置をとる
		 wallCollisions[i] = {
			 wall_->GetWorldTransform()[i].matWorld_.m[3][0],
			 wall_->GetWorldTransform()[i].matWorld_.m[3][1],
			 wall_->GetWorldTransform()[i].matWorld_.m[3][2],
		};
	
		 //全ての壁ブロックとプレイヤーの当たり判定をとる
		 if (CheakCollision(
			 wallCollisions[i], playerCollision,
			 wall_->GetWorldTransform()[i].scale_, player_->GetWorldTransform().scale_)) {
			 isHit[i] = 1;
		 }
		 else {
			 isHit[i] = 0;
		 }
	}

	//箱の回転
	if (player_->GetWorldTransform().translation_.x > worldTransform_.scale_.x) {
		worldTransform_.rotation_ = { 0.0f, 0.0f, radian };
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

	if (isRotateX || isRotateZ) {

		if (isRotateZ) {
			//ステージZ軸回転
			Affine::CreateMatRotZ(worldTransform_, worldTransform_.rotation_);
			Affine::CreateMatRotZ(worldTransform2_, worldTransform_.rotation_);
		}
		else if (isRotateX) {
			//ステージX軸回転
			Affine::CreateMatRotX(worldTransform_, worldTransform_.rotation_);
			Affine::CreateMatRotX(worldTransform2_, worldTransform_.rotation_);
		}

		//壁やプレイヤーはステージに合わせて回転する
		player_->Rotate(worldTransform_);
		wall_->Rotate(worldTransform_);

		rotateTimer += radian;

		if (rotateTimer >= PI / 2) {
			isRotateZ = 0;
			isRotateX = 0;
			rotateTimer = 0;
		}
	}
	else {
		//回転していないときだけプレイヤーは動ける
		player_->Update(wall_->GetWorldTransform(), isHit);
		if (worldTransform2_.matWorld_.m[3][0] > 7.0f || worldTransform2_.matWorld_.m[3][0] < -7.0f ||
			worldTransform2_.matWorld_.m[3][2] > 7.0f || worldTransform2_.matWorld_.m[3][2] < -7.0f) {

			if (worldTransform2_.matWorld_.m[3][1] > -8.0f) {
				Affine::CreateMatTrans(worldTransform2_, { 0.0f,-0.1f,0.0f });
			}
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
	worldTransform2_.TransferMatrix();
	viewProjection_.UpdateMatrix();
	debugCamera_->Update();

	debugText_->SetPos(20, 20);
	debugText_->Printf("%f,%f,%f",
		player_->GetWorldTransform().translation_.x,
		player_->GetWorldTransform().translation_.y,
		player_->GetWorldTransform().translation_.z
	);
	debugText_->SetPos(20, 40);
	debugText_->Printf("%f,%f,%f",
		worldTransform_.matWorld_.m[0][0],
		worldTransform_.matWorld_.m[0][1],
		worldTransform_.matWorld_.m[0][2]
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
	
	//ステージの描画
	model_->Draw(worldTransform_, viewProjection_);
	model2_->Draw(worldTransform2_, viewProjection_,tex);
	//壁ブロックの描画
	wall_->Draw(&viewProjection_);
	//プレイヤーの描画
	player_->Draw(&viewProjection_);

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

//当たり判定
bool GameScene::CheakCollision(Vector3 posA, Vector3 posB, Vector3 sclA, Vector3 sclB) {

	float a = 1.0f;
	sclA = { sclA.x * a,sclA.y * a ,sclA.z * a };
	sclB = { sclB.x * a,sclB.y * a ,sclB.z * a };

	if (posA.x - sclA.x < posB.x + sclB.x && posA.x + sclA.x > posB.x - sclB.x &&
		posA.y - sclA.y < posB.y + sclB.y && posA.y + sclA.y > posB.y - sclB.y &&
		posA.z - sclA.z < posB.z + sclB.z && posA.z + sclA.z > posB.z - sclB.z)
	{
		return true;
	}

	return false;
}
