#include "Core.h"
#include "map.h"
Core::~Core() {
	delete coreModel_;
}

void Core::Initialize(float y)
{
	coreModel_ = Model::LoadFromOBJ("triangle_mat");
	coreObject_ = Object3d::Create();
	coreObject_->SetModel(coreModel_);
	coreObject_->position = { 0.0f,11.5f,0.0f };
	coreObject_->SetPosition(coreObject_->position);
	coreObject_->SetScale({ 1.0f,1.0f,1.0f });
	coreObject_->Update();
	/*textureHandle_ = TextureManager::Load("Core.png");
	coreModel_ = Model::Create();*/

	//worldTransform_.Initialize();
	//worldTransform_.scale_ = { 0.5f,0.5f,0.5f };

	//worldTransform_.translation_ = { 0.0f, y + worldTransform_.scale_.y, 0.0f };//{0.0,7.5,0.0}

	/*Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();*/

	//for (int i = 0; i < leadNum; i++) {
	//	leadWorldTransformsX_[i].Initialize();
	//	leadWorldTransformsY_[i].Initialize();
	//	leadWorldTransformsZ_[i].Initialize();

	//	leadWorldTransformsX_[i].scale_ = { 0.1f,0.1f,0.1f };
	//	leadWorldTransformsY_[i].scale_ = { 0.1f,0.1f,0.1f };
	//	leadWorldTransformsZ_[i].scale_ = { 0.1f,0.1f,0.1f };

	//	/*	leadWorldTransformsX_[i % 30].translation_ =
	//	{
	//		-leadNum / 6.0f + i,
	//		worldTransform_.matWorld_.m[3][1],
	//		worldTransform_.matWorld_.m[3][2]
	//	};
	//	leadWorldTransformsX_[(30 + i) % 60].translation_ =
	//	{
	//		worldTransform_.matWorld_.m[3][0],
	//		-leadNum / 6.0f + i,
	//		worldTransform_.matWorld_.m[3][2]
	//	};
	//	if (i < leadNum / 3 * 1) {
	//	}
	//	if (i >= 30 && i < 60) {
	//	}*/

	//	leadWorldTransformsX_[i].translation_ =
	//	{
	//		-leadNum / 2.0f + i,
	//		worldTransform_.matWorld_.m[3][1],
	//		worldTransform_.matWorld_.m[3][2]
	//	};
	//	leadWorldTransformsY_[i].translation_ =
	//	{
	//		worldTransform_.matWorld_.m[3][0],
	//		-leadNum / 2.0f + i,
	//		worldTransform_.matWorld_.m[3][2]
	//	};
	//	leadWorldTransformsZ_[i].translation_ =
	//	{
	//		worldTransform_.matWorld_.m[3][0],
	//		worldTransform_.matWorld_.m[3][1],
	//		-leadNum / 2.0f + i
	//	};

	/*	Affine::CreateAffine(leadWorldTransformsX_[i]);
		Affine::CreateAffine(leadWorldTransformsY_[i]);
		Affine::CreateAffine(leadWorldTransformsZ_[i]);
		leadWorldTransformsX_[i].TransferMatrix();
		leadWorldTransformsY_[i].TransferMatrix();
		leadWorldTransformsZ_[i].TransferMatrix();*/
	//}
}

void Core::Update()
{
	//�R�A���X�e�[�W�̏�ɂ��鎞
	//if (worldTransform_.matWorld_.m[3][0] < worldTransform.scale_.x && worldTransform_.matWorld_.m[3][0] > -worldTransform.scale_.x &&
	//	worldTransform_.matWorld_.m[3][2] < worldTransform.scale_.z && worldTransform_.matWorld_.m[3][2] > -worldTransform.scale_.z) {
	//	//���x��0�ɂ���
	//	velocity_.y = 0;

	//}
	//else {
	//	for (int i = 0; i < totalBlockNum; i++) {
	//		//�ǂɓ���������
	//		if (collision[i]) {
	//			//�ʒu�������߂��A���x��0�ɂ���
	//			isFall = 0;
	//			worldTransform_.matWorld_.m[3][1] -= velocity_.y - 0.1f;
	//			velocity_.y = 0.0f;
	//		}
	//	}
	//	//�X�e�[�W����]���Ă��Ȃ��Ƃ�
	//	if ((worldTransform.rotation_.x != 0.0f || worldTransform.rotation_.z != 0.0f) && isFall)
	//	{
	//		//���܂ŉ�����������
	//		if (velocity_.y <= 0.5f && worldTransform_.matWorld_.m[3][1] > -worldTransform.scale_.y)
	//		{
	//			velocity_.y -= 0.01f;
	//		}
	//	}
	//}

	//��ԉ��܂ōs������~�܂�
	//if (worldTransform_.matWorld_.m[3][1] < -(worldTransform.scale_.y + 0.4f))
	//{
	//	velocity_.y = 0.0f;
	//	worldTransform_.matWorld_.m[3][1] = -(worldTransform.scale_.y + 0.4f);

	//}

	////�A�t�B���ϊ�
	//worldTransform_.translation_ += velocity_;
	//Affine::CreateMatTrans(worldTransform_, { velocity_.x,velocity_.y,velocity_.z });
	//worldTransform_.TransferMatrix();

	////�w�W�̃A�t�B���ϊ�
	//for (int i = 0; i < leadNum; i++) {

	//	if ((leadWorldTransformsX_[0].matWorld_.m[3][1] - leadWorldTransformsX_[10].matWorld_.m[3][1]) < 2.0f &&
	//		(leadWorldTransformsX_[0].matWorld_.m[3][1] - leadWorldTransformsX_[10].matWorld_.m[3][1]) > -2.0f) {

	//		leadWorldTransformsX_[i].matWorld_.m[3][1] = worldTransform_.matWorld_.m[3][1];
	//		Affine::CreateMatTrans(leadWorldTransformsX_[i], { velocity_.x,velocity_.y,velocity_.z });
	//		leadWorldTransformsX_[i].TransferMatrix();
	//	}
	//	if ((leadWorldTransformsY_[0].matWorld_.m[3][1] - leadWorldTransformsY_[10].matWorld_.m[3][1]) < 2.0f &&
	//		(leadWorldTransformsY_[0].matWorld_.m[3][1] - leadWorldTransformsY_[10].matWorld_.m[3][1]) > -2.0f) {

	//		leadWorldTransformsY_[i].matWorld_.m[3][1] = worldTransform_.matWorld_.m[3][1];
	//		Affine::CreateMatTrans(leadWorldTransformsY_[i], { velocity_.x,velocity_.y,velocity_.z });
	//		leadWorldTransformsY_[i].TransferMatrix();
	//	}
	//	if ((leadWorldTransformsZ_[0].matWorld_.m[3][1] - leadWorldTransformsZ_[10].matWorld_.m[3][1]) < 2.0f &&
	//		(leadWorldTransformsZ_[0].matWorld_.m[3][1] - leadWorldTransformsZ_[10].matWorld_.m[3][1]) > -2.0f) {

	//		leadWorldTransformsZ_[i].matWorld_.m[3][1] = worldTransform_.matWorld_.m[3][1];
	//		Affine::CreateMatTrans(leadWorldTransformsZ_[i], { velocity_.x,velocity_.y,velocity_.z });
	//		leadWorldTransformsZ_[i].TransferMatrix();
	//	}

	//}
	//debugText_->SetPos(50, 120);
	//debugText_->Printf("%f,%f,%f",
	//	leadWorldTransformsX_[0].matWorld_.m[3][0],
	//	leadWorldTransformsX_[9].matWorld_.m[3][1],
	//	leadWorldTransformsX_[9].matWorld_.m[3][2]
	//);
}

void Core::Draw()
{
	coreObject_->Draw();
	/*coreModel_->Draw(worldTransform_, *viewProjection, textureHandle_);*/

	/*for (int i = 0; i < leadNum; i++) {
		coreModel_->Draw(leadWorldTransformsX_[i], *viewProjection, textureHandle_);
		coreModel_->Draw(leadWorldTransformsY_[i], *viewProjection, textureHandle_);
		coreModel_->Draw(leadWorldTransformsZ_[i], *viewProjection, textureHandle_);
	}*/
}

void Core::Rotate(Object3d* obj)
{
	coreObject_->CreateMatRotZ(obj->rotation);
	coreObject_->CreateMatRotX(obj->rotation);
	coreObject_->TransferMatrix();
}				 

//void Core::SetWorldTransform(WorldTransform worldTransform)
//{
//	Affine::CreateMatRotZ(worldTransform_, worldTransform.rotation_);
//	Affine::CreateMatRotX(worldTransform_, worldTransform.rotation_);
//	worldTransform_.TransferMatrix();
//
//	for (int i = 0; i < leadNum; i++) {
//		Affine::CreateMatRotZ(leadWorldTransformsX_[i], worldTransform.rotation_);
//		Affine::CreateMatRotX(leadWorldTransformsX_[i], worldTransform.rotation_);
//		leadWorldTransformsX_[i].TransferMatrix();
//		Affine::CreateMatRotZ(leadWorldTransformsY_[i], worldTransform.rotation_);
//		Affine::CreateMatRotX(leadWorldTransformsY_[i], worldTransform.rotation_);
//		leadWorldTransformsY_[i].TransferMatrix();
//		Affine::CreateMatRotZ(leadWorldTransformsZ_[i], worldTransform.rotation_);
//		Affine::CreateMatRotX(leadWorldTransformsZ_[i], worldTransform.rotation_);
//		leadWorldTransformsZ_[i].TransferMatrix();
//	}
//}
