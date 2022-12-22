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
	//������ԈȊO�Ȃ痎�Ƃ�
	if (worldTransform.rotation_.x != 0.0f || worldTransform.rotation_.z != 0.0f)
	{
		if (velocity_.y <= 0.5f)
		{
			velocity_.y -= 0.01f;
		}
	}

	// �ړ��͈�
	// �����t�߂�Core���X�e�[�W�ɂ߂荞�܂Ȃ��悤�ɂ���
	if (worldTransform_.matWorld_.m[3][1] > worldTransform.scale_.y)
	{
		if (worldTransform_.matWorld_.m[3][0] < worldTransform.scale_.x && worldTransform_.matWorld_.m[3][0] > -worldTransform.scale_.x &&
			worldTransform_.matWorld_.m[3][2] < worldTransform.scale_.z && worldTransform_.matWorld_.m[3][2] > -worldTransform.scale_.z)
		{
			velocity_.y = 0.0f;
			worldTransform_.matWorld_.m[3][1] = worldTransform.scale_.y + 0.5f;
		}
	}
	// �͈͌��E�ɗ������x�~�߂�
	if (worldTransform_.matWorld_.m[3][1] <= -(worldTransform.scale_.y + 0.5f))
	{
		velocity_.y = 0.0f;
		worldTransform_.matWorld_.m[3][1] = -(worldTransform.scale_.y + 0.5f);
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
