#include "Core.h"
#include "Affine.h"

void Core::Initialize(float y)
{
	textureHandle_ = TextureManager::Load("Core.png");
	coreModel_ = Model::Create();

	worldTransform_.Initialize();
	//ƒ[ƒJƒ‹À•W
	worldTransform_.scale_ = { 0.5f,0.5f,0.5f };
	worldTransform_.translation_ = { 0.0f, y + 0.5f, 0.0f };

	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Core::Update(WorldTransform worldTransform, int rotX, int rotZ)
{
	if (rotZ)
	{
		Affine::CreateMatRotZ(worldTransform_, worldTransform.rotation_);
	}
	if (rotX)
	{
		Affine::CreateMatRotX(worldTransform_, worldTransform.rotation_);
	}
	worldTransform_.TransferMatrix();

	CheckRotate(worldTransform.scale_.x, worldTransform.scale_.z);
}

void Core::Draw(ViewProjection* viewProjection)
{
	coreModel_->Draw(worldTransform_, *viewProjection, textureHandle_);
}

void Core::CheckRotate(float scale_x, float scale_z)
{
	//‰ñ“]ŽžCore‚ª‰ñ“]Œã‚Ì–Ê‚É‚¢‚é‚æ‚¤‚É‚·‚é
	if (worldTransform_.translation_.x > scale_x) {
		worldTransform_.translation_.x = -scale_x + 0.1f;
	}
	else if (worldTransform_.translation_.x < -scale_x) {
		worldTransform_.translation_.x = scale_x - 0.1f;
	}
	else if (worldTransform_.translation_.z > scale_z) {
		worldTransform_.translation_.z = -scale_z + 0.1f;
	}
	else if (worldTransform_.translation_.z < -scale_z) {
		worldTransform_.translation_.z = scale_z - 0.1f;
	}

	worldTransform_.TransferMatrix();
}