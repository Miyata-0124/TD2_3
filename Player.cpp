#include "Player.h"
//#include "Affine.h"
#include "map.h"

Player::~Player() {
	delete playerModel_;
	delete playerObject_;
}

void Player::Initialize(float y) {
	//*input_ = Input::GetInstance();
	//textureHandle_ = TextureManager::Load("cube.jpg");
	playerModel_ = Model::LoadFromOBJ("triangle_mat");
	playerObject_ = Object3d::Create();
	playerObject_->SetModel(playerModel_);
	playerObject_->position = { 0.0f,11.5f,-5.0f };
	playerObject_->SetPosition(playerObject_->position);
	playerObject_->SetScale({ 1.0f,1.5f,1.0f });
	playerObject_->Update();

	//worldTransform_.Initialize();
	//worldTransform_.scale_ = { 0.5f,1.0f,0.5f };
	//worldTransform_.translation_ = { 1.0f,y + worldTransform_.scale_.y,1.0f };

	//Affine::CreateAffine(worldTransform_);
	//worldTransform_.UpdateMatWorld();
}

void Player::Update(Input* input) {

	//playerObject_->CreateMatRotZ(worldTransform_,worldTransform_.rotation_);
	//playerObject_->CreateMatRotX(worldTransform_,worldTransform_.rotation_);
	//worldTransform_.UpdateMatWorld();
	//playerObject_->Update();

	//Ž©‹@‚ÌˆÚ“®
	if (input->PushKey(DIK_A)) {

		playerObject_->position.x -= speed;
		
		/*for (int i = 0; i < totalBlockNum; i++) {

			if (collision[i] && worldTransform[i].matWorld_.m[3][0] < worldTransform_.translation_.x) {
				worldTransform_.translation_.x += speed;
			}
		}*/
	}
	
	if (input->PushKey(DIK_D)) {

		playerObject_->position.x += speed;

		/*for (int i = 0; i < totalBlockNum; i++) {
			if (collision[i] && worldTransform[i].matWorld_.m[3][0] > worldTransform_.translation_.x) {
				worldTransform_.translation_.x -= speed;
			}

		}*/
	}
	if (input->PushKey(DIK_W)) {

		playerObject_->position.z += speed;

		/*for (int i = 0; i < totalBlockNum; i++) {
			if (collision[i] && worldTransform[i].matWorld_.m[3][2] > worldTransform_.translation_.z) {
				worldTransform_.translation_.z -= speed;
			}
		}*/

	}
	if (input->PushKey(DIK_S)) {
		playerObject_->position.z -= speed;

		/*for (int i = 0; i < totalBlockNum; i++) {
			if (collision[i] && worldTransform[i].matWorld_.m[3][2] < worldTransform_.translation_.z) {
				worldTransform_.translation_.z += speed;
			}
		}*/
	}

	playerObject_->Update();
}

void Player::Draw() {
	playerObject_->Draw();

}

void Player::CheckRotate(float scale_x, float scale_z) {
	
	//” ‚Ì‰ñ“]
	if (playerObject_->position.x > scale_x) {
		playerObject_->position.x = -scale_x + speed;
	}
	else if (playerObject_->position.x < -scale_x) {
		playerObject_->position.x = scale_x - speed;
	}
	else if (playerObject_->position.z > scale_z) {
		playerObject_->position.z = -scale_z + speed;
	}
	else if (playerObject_->position.z < -scale_z) {
		playerObject_->position.z = scale_z - speed;
	}
	//Affine::CreateAffine(worldTransform_);
	playerObject_->TransferMatrix();
}

//WorldTransform Player::GetWorldTransform() {
//	return worldTransform_;
//}

void Player::Rotate(Object3d* obj) {
	playerObject_->CreateMatRotZ(obj->rotation);
	playerObject_->CreateMatRotX(obj->rotation);
	playerObject_->TransferMatrix();

	CheckRotate(obj->scale.x, obj->scale.z);
}