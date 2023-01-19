#include "Core.h"
#include "Affine.h"
//ƒvƒ‹ƒŠƒN—p

void Core::Initialize(float y)
{
	//textureHandle_ = Model::LoadModel("Core.png");
	coreModel_ = Model::LoadFromOBJ("core");
	coreObject_ = GameObject3D::Create();
	coreObject_->SetModel(coreModel_);
	worldTransform_.Initialize();
	//ƒ[ƒJƒ‹À•W
	worldTransform_.scale_ = { 0.5f,0.5f,0.5f };

	worldTransform_.translation_ = { 0.0f, y + 0.5f, 0.0f };//{0.0,7.5,0.0}

	Affine::CreateAffine(worldTransform_);
	worldTransform_.UpdateMatWorld();

	//debugText_ = DebugText::GetInstance();
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

	//�[�ɂ������̗h��鋓��
	if (worldTransform_.matWorld_.m[3][1] == -(worldTransform.scale_.y + 0.5f))
	{

	}

	//ŒvŽZ
	worldTransform_.rotation_ += rot_;
	worldTransform_.translation_ += velocity_;

	Affine::CreateMatRotZ(worldTransform_, rot_);
	Affine::CreateMatRotX(worldTransform_, rot_);
	Affine::CreateMatTrans(worldTransform_, { velocity_.x,velocity_.y,velocity_.z });
	worldTransform_.UpdateMatWorld();

}

void Core::Draw(ViewProjection* viewProjection)
{
	coreObject_->Draw();
}

void Core::SetWorldTransform(WorldTransform worldTransform)
{
	Affine::CreateMatRotZ(worldTransform_, worldTransform.rotation_);
	Affine::CreateMatRotX(worldTransform_, worldTransform.rotation_);
	worldTransform_.UpdateMatWorld();
}
