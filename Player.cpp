//#include "Player.h"
//#include "Affine.h"
//#include "map.h"

//Player::~Player() {
//	delete playerModel_;
//	delete playerObject_;
//}
//
//void Player::Initialize(float y) {
//	//*input_ = Input::GetInstance();
//	//textureHandle_ = TextureManager::Load("cube.jpg");
//	playerModel_ = Model::LoadFromOBJ("cube");
//	playerObject_ = Object3d::Create();
//	playerObject_->SetModel(playerModel_);
//	playerObject_->SetPosition({20.0f,0.0f,0.0f});
//	playerObject_->Update();
//	//worldTransform_.Initialize();
//	//worldTransform_.scale_ = { 0.5f,1.0f,0.5f };
//	//worldTransform_.translation_ = { 1.0f,y + worldTransform_.scale_.y,1.0f };
//
//	//Affine::CreateAffine(worldTransform_);
//	//worldTransform_.UpdateMatWorld();
//}
//
//void Player::Update() {
//
//	//playerObject_->CreateMatRotZ(worldTransform_,worldTransform_.rotation_);
//	//playerObject_->CreateMatRotX(worldTransform_,worldTransform_.rotation_);
//	//worldTransform_.UpdateMatWorld();
//	//playerObject_->Update();
//
//	////Ž©‹@‚ÌˆÚ“®
//	//if (input_->PushKey(DIK_A)) {
//
//	//	worldTransform_.translation_.x -= speed;
//
//	//	for (int i = 0; i < totalBlockNum; i++) {
//
//	//		if (collision[i] && worldTransform[i].matWorld_.m[3][0] < worldTransform_.translation_.x) {
//	//			worldTransform_.translation_.x += speed;
//	//		}
//	//	}
//	//}
//	//if (input_->PushKey(DIK_D)) {
//
//	//	worldTransform_.translation_.x += speed;
//
//	//	for (int i = 0; i < totalBlockNum; i++) {
//	//		if (collision[i] && worldTransform[i].matWorld_.m[3][0] > worldTransform_.translation_.x) {
//	//			worldTransform_.translation_.x -= speed;
//	//		}
//
//	//	}
//	//}
//	//if (input_->PushKey(DIK_W)) {
//
//	//	worldTransform_.translation_.z += speed;
//	//	for (int i = 0; i < totalBlockNum; i++) {
//	//		if (collision[i] && worldTransform[i].matWorld_.m[3][2] > worldTransform_.translation_.z) {
//	//			worldTransform_.translation_.z -= speed;
//	//		}
//	//	}
//
//
//	//}
//	//if (input_->PushKey(DIK_S)) {
//	//	worldTransform_.translation_.z -= speed;
//	//	for (int i = 0; i < totalBlockNum; i++) {
//	//		if (collision[i] && worldTransform[i].matWorld_.m[3][2] < worldTransform_.translation_.z) {
//	//			worldTransform_.translation_.z += speed;
//	//		}
//	//	}
//
//	//}
//
//	//Affine::CreateAffine(worldTransform_);
//	//worldTransform_.UpdateMatWorld();
//}
//
//void Player::Draw() {
//	playerObject_->Draw();
//
//}
//
//void Player::CheckRotate(float scale_x, float scale_z) {
//	
//	//” ‚Ì‰ñ“]
//	//if (worldTransform_.translation_.x > scale_x) {
//	//	worldTransform_.translation_.x = -scale_x + speed;
//	//}
//	//else if (worldTransform_.translation_.x < -scale_x) {
//	//	worldTransform_.translation_.x = scale_x - speed;
//	//}
//	//else if (worldTransform_.translation_.z > scale_z) {
//	//	worldTransform_.translation_.z = -scale_z + speed;
//	//}
//	//else if (worldTransform_.translation_.z < -scale_z) {
//	//	worldTransform_.translation_.z = scale_z - speed;
//	//}
//	////Affine::CreateAffine(worldTransform_);
//	//worldTransform_.UpdateMatWorld();
//}
//
////WorldTransform Player::GetWorldTransform() {
////	return worldTransform_;
////}
//
////void Player::Rotate(WorldTransform worldTransform) {
////	//Affine::CreateMatRotZ(worldTransform_, worldTransform.rotation_);
////	//Affine::CreateMatRotX(worldTransform_, worldTransform.rotation_);
////	worldTransform_.UpdateMatWorld();
////
////	CheckRotate(worldTransform.scale_.x, worldTransform.scale_.z);
////}