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
	//delete wall_;
	delete goal_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	model_ = Model::CreateFromOBJ("stage", true);

	worldTransform_.Initialize();
	worldTransform_.scale_ = { 7.0f,7.0f,7.0f };
  	worldTransform_.translation_ = { 0.0f,0.0f,0.0f };

	//プレイヤーの生成
	player_ = new Player();
	player_->Initialize(worldTransform_.scale_.y);

	//コアの生成
	core_ = new Core();
	core_->Initialize(worldTransform_.scale_.y);

	//壁ブロックの生成
	//wall_ = new Wall();
	//wall_->Initialize();

	//ゴールの作成
	goal_ = new Goal();
	goal_->Initialize();

	viewProjection_.Initialize();
	viewProjection_.eye = { 0.0f,0.0f,0.0f };
	viewProjection_.UpdateMatrix();
	Affine::CreateAffine(worldTransform_);
  
	worldTransform_.TransferMatrix();
}

void GameScene::Update() {

	/* カメラ関連 */
		if (input_->PushKey(DIK_UP)) {
			viewProjection_.eye.y += 2.0f;
			if (viewProjection_.eye.y > 40)
			{
				viewProjection_.eye.y = 40;
			}
		}
		else {
			viewProjection_.eye = { 15, 20, -20 };
			viewProjection_.target = { 0, 0, 0 };
		}
	if (input_->PushKey(DIK_LEFT)) {
		viewProjection_.eye.x = -25;
		viewProjection_.eye.y = 0;
		viewProjection_.eye.z -= 2.0f;
		if (viewProjection_.eye.z > -25)
		{
			viewProjection_.eye.z = -25;

		}
	}
	if (input_->PushKey(DIK_DOWN)) {
		viewProjection_.eye.y -= 2.0f;
		if (viewProjection_.eye.y > -40)
		{
			viewProjection_.eye.y = -40;
		}
	}
	if (input_->PushKey(DIK_RIGHT)) {
		viewProjection_.eye.x = 25;
		viewProjection_.eye.y = 0;
		viewProjection_.eye.z += 2.0f;
		if (viewProjection_.eye.z < 25)
		{
			viewProjection_.eye.z = 25;

		}
	}
	viewProjection_.UpdateMatrix();
  

	/*当たり判定関連*/
	//プレイヤーの位置をとる
	Vector3 playerCollision = {
		player_->GetWorldTransform().matWorld_.m[3][0],
		player_->GetWorldTransform().matWorld_.m[3][1],
		player_->GetWorldTransform().matWorld_.m[3][2],
	};

	//コアの位置をとる
	Vector3 coreCollision = {
		core_->GetWorldTransform().matWorld_.m[3][0],
		core_->GetWorldTransform().matWorld_.m[3][1],
		core_->GetWorldTransform().matWorld_.m[3][2],
	};

	//プレイヤーとコアの当たり判定
	if (CheakCollision
		(playerCollision, coreCollision,
		player_->GetWorldTransform().scale_, core_->GetWorldTransform().scale_)) {

	}

	for (int i = 0; i < totalBlockNum; i++) {

		//壁ブロックの位置をとる
		/*wallCollisions[i] = {
			wall_->GetWorldTransform()[i].matWorld_.m[3][0],
			wall_->GetWorldTransform()[i].matWorld_.m[3][1],
			wall_->GetWorldTransform()[i].matWorld_.m[3][2],
		};*/

		//全ての壁ブロックとプレイヤーの当たり判定をとる
		/*if (CheakCollision(
			wallCollisions[i], playerCollision,
			wall_->GetWorldTransform()[i].scale_, player_->GetWorldTransform().scale_)) {
			isHitPlayer[i] = 1;
		}
		else {
			isHitPlayer[i] = 0;
		}*/

		/*if (CheakCollision(
			wallCollisions[i], coreCollision,
			wall_->GetWorldTransform()[i].scale_, core_->GetWorldTransform().scale_)) {
			isHitCore[i] = 1;
		}
		else {
			isHitCore[i] = 0;
		}*/
	}


	/*ステージ関連*/
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

	//回転中
	if (isRotateX || isRotateZ) {
		core_->SetIsFall(1);
		if (isRotateZ) {
			Affine::CreateMatRotZ(worldTransform_, worldTransform_.rotation_);
			core_->SetWorldTransform(worldTransform_);
		}
		else if (isRotateX) {
			Affine::CreateMatRotX(worldTransform_, worldTransform_.rotation_);
			core_->SetWorldTransform(worldTransform_);
		}

		//ステージ回転時、プレイヤーも一緒に回転する
		player_->Rotate(worldTransform_);
		//wall_->Rotate(worldTransform_);
		rotateTimer += radian;

		if (rotateTimer >= PI / 2) {
			isRotateZ = 0;
			isRotateX = 0;
			rotateTimer = 0;
		}
	}
	//回転後
	else {
		//player_->Update(wall_->GetWorldTransform(), isHitPlayer);
		//core_->Update(worldTransform_,wall_->GetWorldTransform(), isHitCore);
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
	//goal_->Draw(&viewProjection_);

	//壁ブロックの描画
	//wall_->Draw(&viewProjection_);

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