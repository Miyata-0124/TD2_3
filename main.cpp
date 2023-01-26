//#include "Input.h"
//#include "WinApp.h"
//#include "DirectXCommon.h"
//#include "SpriteCommon.h"
//#include "Sprite.h"
//#include "Object3d.h"
#include "GameScene.h"

//Windowsアプリでのエントリーポイント(main関数)
/*Windows・・・マイクロソフト（Microsoft）社が開発・販売している、コンピュータのオペレーティングシステム（OS）製品のシリーズ名*/
/*エントリーポイント・・・プログラムの実行段階において、プログラムやルーチンの実行する開始位置のこと
C言語の標準でのエントリーポイントは、mainという名前の関数の先頭位置*/
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	GameScene gameScene;

	gameScene.Initialize();
	//ゲームループ
	while (true) {

		//Windowsのメッセージ処理
		if (gameScene.GetWinApp()->ProcessMesseage()) {
			//ゲームループを抜ける
			break;
		}

		gameScene.Update();

		gameScene.Draw();
	
	}

	gameScene.Finalize();

	return 0;
}
