#include "Player.h"
//#include "Affine.h"
#include "map.h"

Player::Player() {
	playerModel_ = Model::LoadFromOBJ("triangle_mat");
	playerObject_ = Object3d::Create();
}

Player::~Player() {
	delete playerModel_;
	delete playerObject_;
}

void Player::Initialize(float y) {

	playerObject_->SetModel(playerModel_);
	playerObject_->position = { 0.0f,12.0f,-3.0f };
	playerObject_->SetPosition(playerObject_->position);
	playerObject_->SetScale({ 1.0f,1.5f,1.0f });
	playerObject_->Update();
}

void Player::Update(Input* input, Object3d* obj, bool* collision) {

	speedX = 0;
	speedZ = 0;

	if (input->PushKey(DIK_A) || input->PushKey(DIK_D) || input->PushKey(DIK_W) || input->PushKey(DIK_S)) {
		if (scale > 1.0f) {
			scaleVal = -scaleVal;
		}
		else if (scale < 0.7f) {
			scaleVal = -scaleVal;
		}

		scale += scaleVal;
	}
	else {
		scale = 1.0f;
	}

	//自機の移動
	if (input->PushKey(DIK_A)) {

		speedX = -MAX_SPEED;

		for (int i = 0; i < totalBlockNum; i++) {

			if (collision[i] && obj[i].GetMatrix().r[3].m128_f32[0] < playerObject_->position.x) {
				speedX = 0;
			}

			//if (input->PushKey(DIK_W)) {
			//	speedZ = MAX_SPEED;
			//}
			//else if (input->PushKey(DIK_S)) {
			//	speedZ = -MAX_SPEED;
			//}
		}
	}
	if (input->PushKey(DIK_D)) {

		speedX = MAX_SPEED;

		for (int i = 0; i < totalBlockNum; i++) {

			if (collision[i] && obj[i].GetMatrix().r[3].m128_f32[0] > playerObject_->position.x) {
				speedX = 0;
			}
		}
	}
	if (input->PushKey(DIK_W)) {

		speedZ = MAX_SPEED;

		for (int i = 0; i < totalBlockNum; i++) {

			if (collision[i] && obj[i].GetMatrix().r[3].m128_f32[2] > playerObject_->position.z) {
				speedZ = 0;
			}
		}

	}
	if (input->PushKey(DIK_S)) {

		speedZ = -MAX_SPEED;

		for (int i = 0; i < totalBlockNum; i++) {

			if (collision[i] && obj[i].GetMatrix().r[3].m128_f32[2] < playerObject_->position.z) {
				speedZ = 0;
			}
		}
	}
	playerObject_->position.x += speedX;
	playerObject_->position.z += speedZ;
	playerObject_->position.y = 13.0f - scale;

	playerObject_->SetScale({ scale,3.0f - scale,scale });
	playerObject_->Update();
}

void Player::Draw() {
	playerObject_->Draw();

}

void Player::CheckRotate(float scale_x, float scale_z) {

	//箱の回転
	if (playerObject_->position.x > scale_x) {
		playerObject_->position.x = -scale_x + 0.2f;
	}
	else if (playerObject_->position.x < -scale_x) {
		playerObject_->position.x = scale_x - 0.2f;
	}
	else if (playerObject_->position.z > scale_z) {
		playerObject_->position.z = -scale_z + 0.2f;
	}
	else if (playerObject_->position.z < -scale_z) {
		playerObject_->position.z = scale_z - 0.2f;
	}

	playerObject_->TransferMatrix();
}

void Player::Rotate(Object3d* obj) {
	playerObject_->CreateMatRotZ(obj->rotation);
	playerObject_->CreateMatRotY(obj->rotation);
	playerObject_->CreateMatRotX(obj->rotation);
	playerObject_->TransferMatrix();

	CheckRotate(obj->scale.x, obj->scale.z);
}