#include "Core.h"
#include "Affine.h"
//ﾆ致ﾆ停ｹﾆ椎ﾆ誰窶廃

void Core::Initialize(float y)
{
	textureHandle_ = TextureManager::Load("Core.png");
	coreModel_ = Model::Create();

	worldTransform_.Initialize();
	//ﾆ陳債ーﾆ谷ﾆ停ｹﾂ催窶｢W
	worldTransform_.scale_ = { 0.5f,0.5f,0.5f };

	worldTransform_.translation_ = { 0.0f, y + 0.5f, 0.0f };//{0.0,7.5,0.0}

	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();

	debugText_ = DebugText::GetInstance();
}

void Core::Update(WorldTransform worldTransform)
{
	//ﾆ嘆ﾂーﾆ停ぎﾅJﾅｽnﾅ津｣窶慊ｮ窶堋｢窶堙・堋｢窶堙遺堋｢窶堙遺堙ｧ
	if (worldTransform.rotation_.x != 0.0f || worldTransform.rotation_.z != 0.0f)
	{
		if (velocity_.y <= 0.5f)
		{
			velocity_.y -= 0.01f;
		}
	}

<<<<<<< HEAD
	// 移動範囲
	// 範囲限界に来たら一度止める
	if (worldTransform_.matWorld_.m[3][1] <= -(worldTransform.scale_.y + 0.4f))
=======
	// ﾋ・壺慊ｮ窶敕才・・
	// 窶敕才・最津ﾅE窶堙俄藩・堋ｽ窶堙ｧﾋ・ｪ窶忸ﾅｽ~窶堙溪堙ｩ
	if (worldTransform_.matWorld_.m[3][1] < -(worldTransform.scale_.y+0.4f))
>>>>>>> 7e5664e20a773e7519d5e507e0861b94b475133b
	{
		velocity_.y = 0.0f;
		worldTransform_.matWorld_.m[3][1] = -(worldTransform.scale_.y + 0.4f);
	}

	//ﾅ致ﾅｽZ
	worldTransform_.translation_ += velocity_;
	Affine::CreateMatTrans(worldTransform_, { velocity_.x,velocity_.y,velocity_.z });
	worldTransform_.TransferMatrix();

}

void Core::Draw(ViewProjection* viewProjection)
{
	coreModel_->Draw(worldTransform_, *viewProjection, textureHandle_);
}

void Core::SetWorldTransform(WorldTransform worldTransform)
{
	Affine::CreateMatRotZ(worldTransform_, worldTransform.rotation_);
	Affine::CreateMatRotX(worldTransform_, worldTransform.rotation_);
	worldTransform_.TransferMatrix();
}
