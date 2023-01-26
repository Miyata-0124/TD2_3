#include "GameScene.h"
#include <cassert>

GameScene::GameScene() {

}

GameScene::~GameScene() {


}

void GameScene::Initialize(WinApp* winApp) {

	//透視投影変換行列の計算
	matProjection_ = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(20.0),
		(float)winApp->window_width / winApp->window_height,
		0.1f, 1000.0f
	);

	viewProjection_.Initialize();
	viewProjection_.eye = { 0 , 100 , -100 };


	//XAudioエンジンのインスタンスを生成
	soundManager_.Initialize();

	field = new Box();
	field->Initialize(&viewProjection_, &matProjection_);
	core = new Core();
	core->Initialize(&viewProjection_, &matProjection_);
}

void GameScene::Update() {
	field->Update();
	core->Update();

}

void GameScene::Draw() {
	//3D描画
	field->Draw();
	//core->Draw();
	//スプライト描画
	Sprite::PreDraw(dx12base_.GetCmdList().Get());


	Sprite::PostDraw();

}

void GameScene::Reset() {


}