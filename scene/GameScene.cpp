#include "GameScene.h"
#include "TextureManager.h"
#include "Affine.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamera_;
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

	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();

	int num = 0;
	for (int i = 0; i < mapHeight;  i++) {
		for (int j = 0; j < mapWidth; j++) {
			worldTransform2_[num].Initialize();
			worldTransform3_[num].Initialize();

			if (map[j][i] == 1) {
				worldTransform2_[num].translation_ = { -6.0f + i * 2.0f,8.0f,6.0f - j * 2.0f};
				worldTransform3_[num].translation_ = {8.0f, -6.0f + i * 2.0f,6.0f - j * 2.0f};
			}

			Affine::CreateAffine(worldTransform2_[num]);
			Affine::CreateAffine(worldTransform3_[num]);
			worldTransform2_[num].TransferMatrix();
			worldTransform3_[num].TransferMatrix();
			num++;
		}
	}

	//プレイヤーの生成
	player_ = new Player();
	player_->Initialize(worldTransform_.scale_.y);

	viewProjection_.Initialize();
	viewProjection_.eye = { 20.0f,20.0f,-30.0f };
	viewProjection_.UpdateMatrix();
}

void GameScene::Update() {
	const float radian = PI / 100.0f;

	Vector3 trans2 = {
		player_->GetWorldTransform().matWorld_.m[3][0],
		player_->GetWorldTransform().matWorld_.m[3][1],
		player_->GetWorldTransform().matWorld_.m[3][2],
	};

	for (int i = 0; i < blockNum; i++) {
		 trans[i] = {
			worldTransform2_[i].matWorld_.m[3][0],
			worldTransform2_[i].matWorld_.m[3][1],
			worldTransform2_[i].matWorld_.m[3][2]
		};
	
		 if (CheakCollision(
			 trans[i], trans2,
			 worldTransform2_[i].scale_, player_->GetWorldTransform().scale_)) {
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

	//ステージ回転時、プレイヤーも一緒に回転する
	player_->Rotate(worldTransform_);

	if (isRotateZ) {
		Affine::CreateMatRotZ(worldTransform_, worldTransform_.rotation_);

		for (WorldTransform& worldTransform2_ : worldTransform2_) {
			Affine::CreateMatRotZ(worldTransform2_, worldTransform_.rotation_);
		}
		for (WorldTransform& worldTransform3_ : worldTransform3_) {
			Affine::CreateMatRotZ(worldTransform3_, worldTransform_.rotation_);
		}
	}
	else if (isRotateX) {
		Affine::CreateMatRotX(worldTransform_, worldTransform_.rotation_);

		for (WorldTransform& worldTransform2_ : worldTransform2_) {
			Affine::CreateMatRotX(worldTransform2_, worldTransform_.rotation_);
		}

		for (WorldTransform& worldTransform2_ : worldTransform2_) {
			Affine::CreateMatRotX(worldTransform2_, worldTransform_.rotation_);
		}
	}
	else {
		player_->Update(worldTransform2_,isHit);
		//player_->Update(worldTransform2_[1],isHit);
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
	for (WorldTransform& worldTransform2_ : worldTransform2_) {
		worldTransform2_.TransferMatrix();

	}

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

	for (WorldTransform& worldTransform2_ : worldTransform2_) {
		debugText_->SetPos(20, 60);
		debugText_->Printf("%d,%d", CheakCollision(
			trans[0], trans2,
			worldTransform2_.scale_, player_->GetWorldTransform().scale_),
			CheakCollision(
				trans[1], trans2,
				worldTransform2_.scale_, player_->GetWorldTransform().scale_));
	}

	debugText_->SetPos(20, 80);
	debugText_->Printf("%d",isHit);
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

	for (WorldTransform& worldTransform2_ : worldTransform2_) {
		model_->Draw(worldTransform2_, viewProjection_);
	}

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
