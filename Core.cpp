#include "Core.h"
#include "Affine.h"

void Core::Initialize(float y)
{
	textureHandle_ = TextureManager::Load("Core.png");
	coreModel_ = Model::Create();

	worldTransform_.Initialize();
	//ローカル座標
	worldTransform_.scale_ = { 0.5f,0.5f,0.5f };
	worldTransform_.translation_ = { 0.0f, y + 0.5f, 0.0f };//{0.0,7.5,0.0}

	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();

	debugText_ = DebugText::GetInstance();
}

void Core::Update(WorldTransform worldTransform)
{
	//向きを確認後滑らす
	if (worldTransform.rotation_.x != 0.0f || worldTransform.rotation_.z != 0.0f)
	{
		if (velocity_.y <= 0.1f)
		{
			velocity_.y -= 0.001f;
		}
		
	}

	// 移動範囲
	// 範囲限界に来たら一度止める
	if (worldTransform_.translation_.y < -worldTransform.scale_.y)
	{
		velocity_.y = 0.0f;
	}

	//計算
	worldTransform_.translation_ += velocity_;
	Affine::CreateMatTrans(worldTransform_, { velocity_.x,velocity_.y,velocity_.z });
	//転送
	worldTransform_.TransferMatrix();

}

void Core::Draw(ViewProjection* viewProjection)
{
	coreModel_->Draw(worldTransform_, *viewProjection, textureHandle_);
}

void Core::SetWorldTransform(WorldTransform worldTransform)
{
	worldTransform_.translation_.y = 7.5f;
	Affine::CreateMatRotZ(worldTransform_, worldTransform.rotation_);
	Affine::CreateMatRotX(worldTransform_, worldTransform.rotation_);
	worldTransform_.TransferMatrix();
}
