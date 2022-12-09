#include "Core.h"
#include "Affine.h"

void Core::Initialize(float y)
{
	textureHandle_ = TextureManager::Load("Core.png");
	coreModel_ = Model::Create();

	worldTransform_.Initialize();
	worldTransform_.scale_ = { 0.5f,0.5f,0.5f };
	worldTransform_.translation_ = { 1.0f,y + 0.5f,2.0f };

	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Core::Update()
{
	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Core::Draw(ViewProjection& viewProjection)
{
	coreModel_->Draw(worldTransform_, viewProjection,textureHandle_);
}
