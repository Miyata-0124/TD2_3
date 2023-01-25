#pragma once
#include "GameObject3D.h"
#include "MathFunc.h"

class Box {
public:	//メンバ関数
	//インストラクタ
	Box();
	//デストラクタ
	~Box();

	//初期化
	void Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection);
	//モデル読み込み
	void GetModel();
	//更新
	void Update();
	//描画
	void Draw();

private:	//メンバ変数

	//ステージ
	GameObject3D* field = nullptr;
};
