#include "Player.h"
#include "Affine.h"
#include "map.h"

Player::~Player() {
	delete playerModel_;
}

void Player::Initialize(float y) {
	input_ = Input::GetInstance();
	textureHandle_ = TextureManager::Load("cube.jpg");
	playerModel_ = Model::Create();

	worldTransform_.Initialize();
	worldTransform_.scale_ = { 0.5f,1.0f,0.5f };
	worldTransform_.translation_ = { 1.0f,y + worldTransform_.scale_.y,1.0f };

	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Player::Update(WorldTransform* worldTransform, bool* collision) {

	//自機の移動
	if (input_->PushKey(DIK_A)) {

		worldTransform_.translation_.x -= speed;

		for (int i = 0; i < totalBlockNum; i++) {

			if (collision[i] && worldTransform[i].matWorld_.m[3][0] < worldTransform_.translation_.x) {
				worldTransform_.translation_.x += speed;
			}
		}
	}
	if (input_->PushKey(DIK_D)) {

		worldTransform_.translation_.x += speed;

		for (int i = 0; i < totalBlockNum; i++) {
			if (collision[i] && worldTransform[i].matWorld_.m[3][0] > worldTransform_.translation_.x) {
				worldTransform_.translation_.x -= speed;
			}

		}
	}
	if (input_->PushKey(DIK_W)) {

		worldTransform_.translation_.z += speed;
		for (int i = 0; i < totalBlockNum; i++) {
			if (collision[i] && worldTransform[i].matWorld_.m[3][2] > worldTransform_.translation_.z) {
				worldTransform_.translation_.z -= speed;
			}
		}


	}
	if (input_->PushKey(DIK_S)) {
		worldTransform_.translation_.z -= speed;
		for (int i = 0; i < totalBlockNum; i++) {
			if (collision[i] && worldTransform[i].matWorld_.m[3][2] < worldTransform_.translation_.z) {
				worldTransform_.translation_.z += speed;
			}
		}

	}

	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection* viewProjection) {
	playerModel_->Draw(worldTransform_, *viewProjection, textureHandle_);

}

void Player::CheckRotate(float scale_x, float scale_z) {
	//箱の回転
	if (worldTransform_.translation_.x > scale_x) {
		worldTransform_.translation_.x = -scale_x + speed;
	}
	else if (worldTransform_.translation_.x < -scale_x) {
		worldTransform_.translation_.x = scale_x - speed;
	}
	else if (worldTransform_.translation_.z > scale_z) {
		worldTransform_.translation_.z = -scale_z + speed;
	}
	else if (worldTransform_.translation_.z < -scale_z) {
		worldTransform_.translation_.z = scale_z - speed;
	}
	//Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();
}

WorldTransform Player::GetWorldTransform() {
	return worldTransform_;
}

void Player::Rotate(WorldTransform worldTransform) {
	Affine::CreateMatRotZ(worldTransform_, worldTransform.rotation_);
	Affine::CreateMatRotX(worldTransform_, worldTransform.rotation_);
	worldTransform_.TransferMatrix();

	CheckRotate(worldTransform.scale_.x, worldTransform.scale_.z);
}