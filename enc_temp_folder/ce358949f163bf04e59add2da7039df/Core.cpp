#include "Core.h"
#include "Affine.h"
//ƒvƒ‹ƒŠƒN—p

void Core::Initialize(float y)
{
	textureHandle_ = TextureManager::Load("Core.png");
	coreModel_ = Model::Create();

	worldTransform_.Initialize();
	//ƒ[ƒJƒ‹À•W
	worldTransform_.scale_ = { 0.5f,0.5f,0.5f };

	worldTransform_.translation_ = { 0.0f, y + 0.5f, 0.0f };//{0.0,7.5,0.0}

	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();

	debugText_ = DebugText::GetInstance();
}

void Core::Update(WorldTransform worldTransform)
{
	//ƒQ[ƒ€ŠJŽnŒã“®‚¢‚ÁE��¢‚È‚¢‚È‚ç
	if (worldTransform.rotation_.x != 0.0f || worldTransform.rotation_.z != 0.0f)
	{
		if (velocity_.y <= 0.5f)
		{
			velocity_.y -= 0.01f;
		}
	}

<<<<<<< HEAD
	// �ړ��͈�
	// �͈͌��E�ɗ������x�~�߂�
	if (worldTransform_.matWorld_.m[3][1] <= -(worldTransform.scale_.y + 0.4f))
=======
	// ˁE�“®”ÍˁE�E
	// ”ÍˁE�ŒÀŠE‚É—ˁE��½‚çˁE�“xŽ~‚ß‚é
	if (worldTransform_.matWorld_.m[3][1] < -(worldTransform.scale_.y+0.4f))
>>>>>>> 7e5664e20a773e7519d5e507e0861b94b475133b
	{
		velocity_.y = 0.0f;
		worldTransform_.matWorld_.m[3][1] = -(worldTransform.scale_.y + 0.4f);
	}

	//ŒvŽZ
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
