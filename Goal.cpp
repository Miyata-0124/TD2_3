#include "Goal.h"
#include "map.h"

Goal::Goal() {
	goalModel_ = Model::LoadFromOBJ("Goal");
	goalObject_ = Object3d::Create();
}

Goal::~Goal() {
	delete goalModel_;
	delete goalObject_;
}
void Goal::Initialize(float y)
{
	goalObject_->SetModel(goalModel_);

	goalObject_->position = { 7.0f,-y - 1.5f,-8.0f };
	goalObject_->SetPosition(goalObject_->position);
	goalObject_->SetScale({ 1.0f,1.0f,1.0f });
	goalObject_->Update();
}

//void Goal::Update()
void Goal::Update()
{
	//goalObject_->SetPosition(goalObject_->position);
	goalObject_->TransferMatrix();
}
void Goal::Draw()
{
	goalObject_->Draw();
	/*coreModel_->Draw(worldTransform_, *viewProjection, textureHandle_);*/
	/*for (int i = 0; i < leadNum; i++) {
		coreModel_->Draw(leadWorldTransformsX_[i], *viewProjection, textureHandle_);
		coreModel_->Draw(leadWorldTransformsY_[i], *viewProjection, textureHandle_);
		coreModel_->Draw(leadWorldTransformsZ_[i], *viewProjection, textureHandle_);
	}*/
}
void Goal::Rotate(Object3d* obj)
{
	goalObject_->CreateMatRotZ(obj->rotation);
	goalObject_->CreateMatRotX(obj->rotation);
	goalObject_->TransferMatrix();
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