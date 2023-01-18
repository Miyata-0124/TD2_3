#include "Audio.h"
#include "DX12base.h"
#include "GameScene.h"
#include "Texture.h"
#include "WinApp.h"
//#include "AxisIndicator.h"
//include "PrimitiveDrawer.h"

//WinApp winApp_;
using namespace DirectX;
using namespace Microsoft::WRL;

#pragma region//関数のプロトタイプ宣言
//ウィンドウプロシーシャ
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

#pragma endregion//関数のプロトタイプ宣言

//main関数
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	WinApp* win = nullptr;
	win->Initialize();
	DX12base* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText* debugText = nullptr;
	//AxisIndicator* axisIndicator = nullptr;
	//PrimitiveDrawer* primitiveDrawer = nullptr;
	GameScene* gameScene = nullptr;

	// ゲームウィンドウの作成
	//n = WinApp::GetInstance();
	//n->CreateGameWindow();

	// DirectX初期化処理
	*dxCommon = DX12base::GetInstance();
	dxCommon->Initialize();

#pragma region 汎用機能初期化
	// 入力の初期化
	*input = Input::GetInstance();
	//input->Initialize();

	// オーディオの初期化
	//audio = Audio::GetInstance();
	//audio->Initialize();

	// テクスチャマネージャの初期化
	//Texture::GetInstance()->Initialize(dxCommon->GetDevice());
	//Texture::Load("white1x1.png");

	// スプライト静的初期化
	//Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// デバッグテキスト初期化
	debugText = DebugText::GetInstance();
	debugText->Initialize();

	// 3Dモデル静的初期化
	//Model::StaticInitialize();

	// 軸方向表示初期化
	//axisIndicator = AxisIndicator::GetInstance();
	//axisIndicator->Initialize();

	//primitiveDrawer = PrimitiveDrawer::GetInstance();
	//primitiveDrawer->Initialize();

#pragma endregion

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize(win);

#pragma region//ゲームループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMesseage()) {
			break;
		}

		// 入力関連の毎フレーム処理
		input->Update();
		// ゲームシーンの毎フレーム処理
		gameScene->Update();
		// 軸表示の更新
		//axisIndicator->Update();

		// 描画開始
		dxCommon->PreDraw();
		// ゲームシーンの描画
		gameScene->Draw();
		// 軸表示の描画
		//axisIndicator->Draw();
		// プリミティブ描画のリセット
		//primitiveDrawer->Reset();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	//SafeDelete(gameScene);
	delete gameScene;
	//audio->Finalize();

	// ゲームウィンドウの破棄
	//win->TerminateGameWindow();
	win->Finalize();
	return 0;
}