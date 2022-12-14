#include "Core.h"
#include "Affine.h"

void Core::Initialize(float y, WorldTransform boxTransform)
{
	textureHandle_ = TextureManager::Load("Core.png");
	coreModel_ = Model::Create();

	worldTransform_.Initialize();
	//ƒ[ƒJƒ‹À•W
	worldTransform_.scale_ = { 0.1f,0.1f,0.1f };
	worldTransform_.translation_ = { 0.0f, 1.1f, 0.0f };
	worldTransform_.parent_ = &boxTransform;

	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Core::Update(Matrix4 boxMat)
{
	Affine::CreateAffine(worldTransform_);

	worldTransform_.matWorld_ *= boxMat;

	worldTransform_.TransferMatrix();
}

void Core::Draw(ViewProjection* viewProjection)
{
	coreModel_->Draw(worldTransform_, *viewProjection, textureHandle_);
}
