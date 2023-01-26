#include "Core.h"

//ﾆ致ﾆ停ｹﾆ椎ﾆ誰窶廃
void Core::Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection)
{
	core = new GameObject3D();
	core->PreLoadModel("Resources/core/core.obj");
	core->PreLoadTexture(L"Resources/core/core.png");
	core->SetViewProjection(viewProjection);
	core->SetMatProjection(matProjection);
	core->Initialize();
	core->worldTransform.rotation = { 5,5,5 };
}

void Core::Update()
{
	core->Update();
	////初期状態以外なら落とす
	//if (worldTransform.rotation_.x != 0.0f || worldTransform.rotation_.z != 0.0f)
	//{
	//	if (velocity_.y <= 0.5f)
	//	{
	//		velocity_.y -= 0.01f;
	//	}
	//}

	//// 移動範囲
	//// 中央付近でCoreがステージにめり込まないようにする
	//if (worldTransform_.matWorld_.m[3][1] > worldTransform.scale_.y)
	//{
	//	if (worldTransform_.matWorld_.m[3][0] < worldTransform.scale_.x && worldTransform_.matWorld_.m[3][0] > -worldTransform.scale_.x &&
	//		worldTransform_.matWorld_.m[3][2] < worldTransform.scale_.z && worldTransform_.matWorld_.m[3][2] > -worldTransform.scale_.z)
	//	{
	//		velocity_.y = 0.0f;
	//		worldTransform_.matWorld_.m[3][1] = worldTransform.scale_.y + 0.5f;
	//	}
	//}
	//// 範囲限界に来たら一度止める
	//if (worldTransform_.matWorld_.m[3][1] <= -(worldTransform.scale_.y + 0.5f))
	//{
	//	velocity_.y = 0.0f;
	//	worldTransform_.matWorld_.m[3][1] = -(worldTransform.scale_.y + 0.5f);
	//}

	////端についた時の揺れる挙動
	//if (worldTransform_.matWorld_.m[3][1] == -(worldTransform.scale_.y + 0.5f))
	//{

	//}

	////ﾅ致ﾅｽZ
	//worldTransform_.rotation_ += rot_;
	//worldTransform_.translation_ += velocity_;

	//Affine::CreateMatRotZ(worldTransform_, rot_);
	//Affine::CreateMatRotX(worldTransform_, rot_);
	//Affine::CreateMatTrans(worldTransform_, { velocity_.x,velocity_.y,velocity_.z });
	//worldTransform_.TransferMatrix();

}

void Core::Draw()
{
	core->Draw();
	//coreModel_->Draw(worldTransform_, *viewProjection, textureHandle_);
}