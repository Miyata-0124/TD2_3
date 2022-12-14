#include "Player.h"
#include "Affine.h"

Player::~Player() {
	delete playerModel_;
}

void Player::Initialize(float y) {
	input_ = Input::GetInstance();
	textureHandle_ = TextureManager::Load("cube.jpg");
	playerModel_ = Model::Create();

	worldTransform_.Initialize();
	worldTransform_.scale_ = { 0.5f,0.5f,0.5f };
	worldTransform_.translation_ = { 1.0f,y + 0.5f,1.0f };
  
	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Player::Update() {

	if (input_->PushKey(DIK_A)) {
		worldTransform_.translation_.x -= 0.2f;
	}
	if (input_->PushKey(DIK_D)) {
		worldTransform_.translation_.x += 0.2f;
	}
	if (input_->PushKey(DIK_W)) {
		worldTransform_.translation_.z += 0.2f;
	}
	if (input_->PushKey(DIK_S)) {
		worldTransform_.translation_.z -= 0.2f;
	}

	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection* viewProjection) {
	playerModel_->Draw(worldTransform_, *viewProjection, textureHandle_);


void Player::CheckRotate(float scale_x, float scale_z) {
	//” ‚Ì‰ñ“]
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

	//Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();
}

WorldTransform Player::GetWorldTransform() {
	return worldTransform_;
}

void Player::SetWorldTransform(WorldTransform worldTransform) {
	//worldTransform_.matWorld_ *= matrix;
	Affine::CreateMatRotZ(worldTransform_,worldTransform.rotation_);
	Affine::CreateMatRotX(worldTransform_,worldTransform.rotation_);
	worldTransform_.TransferMatrix();

	CheckRotate(worldTransform.scale_.x, worldTransform.scale_.z);

}