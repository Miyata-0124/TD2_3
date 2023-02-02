#include "GameScene.h"
//#include "Affine.h"

void GameScene::Initialize() {
	//コンソールへの文字出力
	//コンソール・・・広義でパソコン全般の入力・出力用の装置のことを指し、主にキーボードやディスプレイのこと
	//OutputDebugStringA("Hello,DirectX!!\n");

	//WindowsAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();

	//DirectX初期化処理 ここから
	//DirectX・・・マイクロソフトが開発したゲーム・マルチメディア処理用のAPIの集合
	//API・・・Application Programming Interfaceの略
	//ソフトウェアからOSの機能を利用するための仕様またはインターフェース(両者の間で情報や信号などをやりとりするための手順や規約を定めたもの)の総称
	//アプリケーションの開発を容易にするためのソフトウェア資源のことをいう
	//HRESULT result;

	//DirectXの初期化
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//入力の初期化
	input = new Input();
	input->Initialize(winApp);

	//3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	//描画初期化ここから

	//カメラの初期化
	Object3d::SetEye({ 14.5f,23.0f,-14.5f });
	Object3d::SetTarget({ 1, 0, -1 });

	//スプライト共通部の初期化
	spriteCommon = new SpriteCommon();
	spriteCommon->Initialize(dxCommon);

	//テクスチャ読み込み
	spriteCommon->LoadTexture(1, "reimu.png");
	spriteCommon->LoadTexture(0, "mario.jpg");

	sprite->Initialize(spriteCommon);
	sprite1->Initialize(spriteCommon);

	stageObject = Object3d::Create();
	//object3d2 = Object3d::Create();
	model = Model::LoadFromOBJ("cube");
	model2 = Model::LoadFromOBJ("triangle_mat");
	//オブジェクトにモデルをひもづける
	stageObject->SetModel(model);
	//object3d2->SetModel(model2);

	stageObject->SetScale({ 10.0f,10.0f,10.0f });

	//プレイヤーの生成
	player_ = new Player();
	player_->Initialize(0.0f);
	//コアの生成
	core_ = new Core();
	core_->Initialize(stageObject->scale.y);
	//ゴールの生成
	goal_ = new Goal();
	goal_->Initialize(stageObject->scale.y);
	//壁ブロックの生成
	wall_ = new Wall();
	wall_->Initialize();

	viewProjection_.Initialize();
	viewProjection_.eye = { 20.0f,20.0f,-30.0f };
	viewProjection_.UpdateView();
	//Affine::CreateAffine(worldTransform_);
	stageObject->Update();

	//worldTransform_.UpdateMatWorld();
	//worldTransform_.Initialize();
	//worldTransform_.scale_ = { 7.0f,7.0f,7.0f };
	//worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
	//Affine::CreateAffine(worldTransform_);
	//worldTransform_.UpdateMatWorld();
}

void GameScene::Finalize() {
	//WindowsAPIの終了処理
	winApp->Finalize();

	//スプライト解放
	delete sprite;
	delete sprite1;
	delete spriteCommon;
	//3Dオブジェクト解放
	delete stageObject;
	//delete object3d2;
	//3Dモデル解放
	delete model;
	delete model2;
	delete player_;
	delete core_;
	delete wall_;
	delete goal_;
	//DirectX解放
	delete dxCommon;
	//入力解放
	delete input;
	//WindowsAPI解放
	delete winApp;

}

void GameScene::Update() {


	//DirectX毎フレーム処理 ここから

	//入力の更新
	input->Update();
	//sprite->Update(spriteCommon);
	if (input->PushKey(DIK_UP)) {
		viewProjection_.eye.y += 2.5f;
		if (viewProjection_.eye.y > 50)
		{
			viewProjection_.eye.y = -0.01;
			viewProjection_.eye.z = -0.01;
		}
	}
	else {
		viewProjection_.eye = { 0, 0, -50 };
		viewProjection_.target = { 0, 0, 0 };
	}
	if (input->PushKey(DIK_LEFT)) {
		viewProjection_.eye = { -50, 0, 0 };
	}
	if (input->PushKey(DIK_DOWN)) {
		viewProjection_.eye = { 0, -50, -0.01 };
	}
	if (input->PushKey(DIK_RIGHT)) {
		viewProjection_.eye = { 50, 0, 0 };
	}
	viewProjection_.UpdateView();
	switch (scene)
	{
	case 0:// タイトル
		if (input->PushKey(DIK_SPACE)) {
			scene = 1;
		}
		break;
	case 1:// ゲームプレイ
#pragma region ゲームプレイ
		/*当たり判定関連*/
//プレイヤーの位置をとる
		XMFLOAT3 playerCollision =
		{
			player_->GetTransform()->matWorld.r[3].m128_f32[0],
			player_->GetTransform()->matWorld.r[3].m128_f32[1],
			player_->GetTransform()->matWorld.r[3].m128_f32[2],
		};

		XMFLOAT3 coreCollision =
		{
			core_->GetTransform()->matWorld.r[3].m128_f32[0],
			core_->GetTransform()->matWorld.r[3].m128_f32[1],
			core_->GetTransform()->matWorld.r[3].m128_f32[2],
		};

		for (int i = 0; i < totalBlockNum; i++) {

			//壁ブロックの位置をとる
			wallCollisions[i] =
			{
				wall_->GetTransform()[i].matWorld.r[3].m128_f32[0],
				wall_->GetTransform()[i].matWorld.r[3].m128_f32[1],
				wall_->GetTransform()[i].matWorld.r[3].m128_f32[2],
			};

			//全ての壁ブロックとプレイヤーの当たり判定をとる
			if (CheakCollision(
				wallCollisions[i], playerCollision,
				wall_->GetScale(), player_->GetScale())) {
				isHitPlayer[i] = 1;
			}
			else {
				isHitPlayer[i] = 0;
			}


			if (CheakCollision(
				wallCollisions[i], coreCollision,
				wall_->GetScale(), core_->GetTransform()->scale)) {
				isHitCore[i] = 1;
			}
			else {
				isHitCore[i] = 0;
			}
		}

		if (CheakCollision(
			wallCollisions[0], playerCollision,
			wall_->GetScale(), player_->GetScale())) {
			isHitPlayer[0] = 1;
		}
		else {
			isHitPlayer[0] = 0;
		}


		/*ステージ関連*/
		//箱の回転
		if (player_->GetPosition().x > stageObject->scale.x) {
			stageObject->rotation = { 0.0f, 0.0f, radian };
			isRotateZ = 1;
		}
		else if (player_->GetPosition().x < -stageObject->scale.x) {
			stageObject->rotation = { 0.0f, 0.0f, -radian };
			isRotateZ = 1;
		}
		else if (player_->GetPosition().z > stageObject->scale.z) {
			stageObject->rotation = { -radian, 0.0f, 0.0f };
			isRotateX = 1;
		}
		else if (player_->GetPosition().z < -stageObject->scale.z) {
			stageObject->rotation = { radian, 0.0f, 0.0f };
			isRotateX = 1;
		}

		//回転中
		if (isRotateX || isRotateZ) {
			core_->SetIsFall(1);
			if (isRotateZ) {
				stageObject->CreateMatRotZ(stageObject->rotation);
				//core_->SetWorldTransform(worldTransform_);
			}
			else if (isRotateX) {
				stageObject->CreateMatRotX(stageObject->rotation);
				//core_->SetWorldTransform(worldTransform_);
			}

			//ステージ回転時、プレイヤーも一緒に回転する
			player_->Rotate(stageObject);
			wall_->Rotate(stageObject);
			core_->Rotate(stageObject);
			goal_->Rotate(stageObject);
			//wall_->Rotate(worldTransform_);
			rotateTimer += radian;

			if (rotateTimer >= 90.0f) {
				isRotateZ = 0;
				isRotateX = 0;
				rotateTimer = 0;
			}
		}
		//回転後
		else {
			player_->Update(input, wall_->GetTransform(), isHitPlayer);
			core_->Update(stageObject, isHitCore);
			//core_->Update(worldTransform_,wall_->GetWorldTransform(), isHitCore);
		}

		////一周したら0に戻す
		//if (worldTransform_.rotation_.x >= PI * 2 || worldTransform_.rotation_.x <= -PI * 2) {
		//	worldTransform_.rotation_.x = 0.0f;
		//}

		//if (worldTransform_.rotation_.z >= PI * 2 || worldTransform_.rotation_.z <= -PI * 2) {
		//	worldTransform_.rotation_.z = 0.0f;
		//}

		//worldTransform_.TransferMatrix();
#pragma endregion
		if (input->PushKey(DIK_R)) { //クリア条件ができるまで使用
			scene = 2;
		}
		break;
	case 2:// クリア
		if (input->PushKey(DIK_SPACE)) {
			scene = 0;
		}
		break;
	}
	
}

void GameScene::Draw() {
	//描画前処理
	dxCommon->PreDraw();

	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());
	switch (scene)
	{
	case 0:// タイトル
		break;
	case 1:// ゲームプレイ
#pragma region ゲームプレイ
		//3Dオブジェクトの描画
		stageObject->Draw();
		//object3d2->Draw();
		player_->Draw();
		core_->Draw();
		wall_->Draw();
		goal_->Draw();
#pragma endregion
		break;
	case 2:// クリア
		break;
	}
	
	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	//スプライト描画前処理
	spriteCommon->PreDraw();

	////描画コマンドここから
	spriteCommon->Update(dxCommon);
	//sprite->SetPosition(position);
	sprite1->SetPosition({ 100.0f,100.0f });
	sprite->SetIndex(0);
	sprite1->SetIndex(1);
	//sprite1->SetTextureSize({ 500.0f,450.0f });

	//sprite->Draw(spriteCommon);
	//sprite1->Draw(spriteCommon);
	////描画コマンドここまで

	//スプライト描画後処理
	spriteCommon->PostDraw();


	dxCommon->PostDraw();


	//DirectX毎フレーム処理 ここまで
}

//当たり判定
bool GameScene::CheakCollision(XMFLOAT3 posA, XMFLOAT3 posB, XMFLOAT3 sclA, XMFLOAT3 sclB) {

	float a = 1.1f;
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
