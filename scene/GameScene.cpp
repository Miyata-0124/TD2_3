#include "GameScene.h"
#include "Texture.h"
#include "Affine.h"
#include <cassert>

GameScene::GameScene() {

}

GameScene::~GameScene() {
	delete stageModel_;
	delete player_;
	//delete debugCamera_;
	delete core_;
	delete wall_;
	//delete goal_;

}

void GameScene::Initialize(WinApp* winApp) {
	*dx12base_ = DX12base::GetInstance();
	*input_ = Input::GetInstance();
	//audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	stageModel_ = Model::LoadFromOBJ("Box");
	stageObject_ = GameObject3D::Create();
	stageObject_->SetModel(stageModel_);
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
	wall_ = new Wall();
	wall_->Initialize();

	//ゴールの作成
	//goal_ = new Goal();
	//goal_->Initialize();

	viewProjection_.Initialize();
	viewProjection_.eye = { 0.0f,0.0f,0.0f };
	viewProjection_.UpdateView();
	Affine::CreateAffine(worldTransform_);

	worldTransform_.UpdateMatWorld();

}

void GameScene::Update() {

	//isPlayingBGM2 = false;
	//シーン管理
	switch (scene_) {
	case GameScene::Scene::Title:


		if (input_->TriggerKey(DIK_SPACE)) {
			scene_ = GameScene::Scene::Stage;
		}

		break;
	case GameScene::Scene::Stage:
		/*カメラ関連*/
		if (input_->PushKey(DIK_UP)) {
			viewProjection_.eye.y += 2.5f;
			if (viewProjection_.eye.y > 50)
			{
				viewProjection_.eye.y = 50;
			}
		}
		else {
			viewProjection_.eye = { 20, 20, -20 };
			viewProjection_.target = { 0, 0, 0 };
		}
		if (input_->PushKey(DIK_LEFT)) {
			viewProjection_.eye.x -= 2.5f;
			if (viewProjection_.eye.x > -20)
			{
				viewProjection_.eye.x = -20;

			}
		}
		if (input_->PushKey(DIK_DOWN)) {
			viewProjection_.eye.y -= 2.5f;
			if (viewProjection_.eye.y > -50)
			{
				viewProjection_.eye.y = -50;
			}
		}
		if (input_->PushKey(DIK_RIGHT)) {
			viewProjection_.eye.z += 2.5f;
			if (viewProjection_.eye.z < 20)
			{
				viewProjection_.eye.z = 20;

			}
		}
		viewProjection_.UpdateView();


		/*当たり判定関連*/
		//プレイヤーの位置をとる
		

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


		/*ステージ関連*/
		
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

		//回転中
		if (isRotateX || isRotateZ) {
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
			wall_->Rotate(worldTransform_);
			rotateTimer += radian;

			if (rotateTimer >= PI / 2) {
				isRotateZ = 0;
				isRotateX = 0;
				rotateTimer = 0;
			}
		}
		//回転後
		else {
			player_->Update(wall_->GetWorldTransform(), isHit);
			core_->Update(worldTransform_);
		}

		//一周したら0に戻す
		if (worldTransform_.rotation_.x >= PI * 2 || worldTransform_.rotation_.x <= -PI * 2) {
			worldTransform_.rotation_.x = 0.0f;
		}

		if (worldTransform_.rotation_.z >= PI * 2 || worldTransform_.rotation_.z <= -PI * 2) {
			worldTransform_.rotation_.z = 0.0f;
		}

		worldTransform_.UpdateMatWorld();

		//debugCamera_->Update();
		
	case GameScene::Scene::Clear:
		if (input_->TriggerKey(DIK_SPACE)) {
			scene_ = GameScene::Scene::Title;
		}
		break;
	}//scene
}
void GameScene::Draw() {
	//3D描画
	switch (scene_) {
	case GameScene::Scene::Title:

		break;
	case GameScene::Scene::Stage:
		stageObject_->Draw();
		player_->Draw(&viewProjection_);
		core_->Draw(&viewProjection_);
		//goal_->Draw(&viewProjection_);
		wall_->Draw(&viewProjection_);
		
	case GameScene::Scene::Clear:

		break;
	}

	//スプライト描画
	Sprite::PreDraw(dx12base_->GetCmdList().Get());
	switch (scene_) {
	case GameScene::Scene::Title:

		break;
	case GameScene::Scene::Stage:

		break;
	case GameScene::Scene::Clear:

		break;
	}
	Sprite::PostDraw();
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
void GameScene::Reset() {


}
