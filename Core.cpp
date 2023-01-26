#include "Core.h"

//ƒvƒ‹ƒŠƒN—p
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
	////������ԈȊO�Ȃ痎�Ƃ�
	//if (worldTransform.rotation_.x != 0.0f || worldTransform.rotation_.z != 0.0f)
	//{
	//	if (velocity_.y <= 0.5f)
	//	{
	//		velocity_.y -= 0.01f;
	//	}
	//}

	//// �ړ��͈�
	//// �����t�߂�Core���X�e�[�W�ɂ߂荞�܂Ȃ��悤�ɂ���
	//if (worldTransform_.matWorld_.m[3][1] > worldTransform.scale_.y)
	//{
	//	if (worldTransform_.matWorld_.m[3][0] < worldTransform.scale_.x && worldTransform_.matWorld_.m[3][0] > -worldTransform.scale_.x &&
	//		worldTransform_.matWorld_.m[3][2] < worldTransform.scale_.z && worldTransform_.matWorld_.m[3][2] > -worldTransform.scale_.z)
	//	{
	//		velocity_.y = 0.0f;
	//		worldTransform_.matWorld_.m[3][1] = worldTransform.scale_.y + 0.5f;
	//	}
	//}
	//// �͈͌��E�ɗ������x�~�߂�
	//if (worldTransform_.matWorld_.m[3][1] <= -(worldTransform.scale_.y + 0.5f))
	//{
	//	velocity_.y = 0.0f;
	//	worldTransform_.matWorld_.m[3][1] = -(worldTransform.scale_.y + 0.5f);
	//}

	////�[�ɂ������̗h��鋓��
	//if (worldTransform_.matWorld_.m[3][1] == -(worldTransform.scale_.y + 0.5f))
	//{

	//}

	////ŒvŽZ
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