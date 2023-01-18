#include "Goal.h"

void Goal::Initialize(float y)
{
	goalModel_->CreateFromOBJ("goal1", true);

	worldTransform_.Initialize();
	worldTransform_.scale_ = { 5.0f,5.0f,5.0f };
	worldTransform_.rotation_ = { 0.0f,0.0f,0.0f };
	worldTransform_.translation_ = { 0.0f, y + 0.5f,0.0f };

	worldTransform_.TransferMatrix();
}

void Goal::Update(WorldTransform worldTransform)
{
}

void Goal::Draw(ViewProjection& viewProjection)
{
	goalModel_->Draw(worldTransform_, viewProjection);
}
