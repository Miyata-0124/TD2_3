#include "Core.h"
#include "Affine.h"
#include "map.h"
//ƒvƒ‹ƒŠƒN—p

void Core::Initialize(float y)
{
	textureHandle_ = TextureManager::Load("Core.png");
	coreModel_ = Model::Create();

	worldTransform_.Initialize();
	worldTransform_.scale_ = { 0.5f,0.5f,0.5f };

	worldTransform_.translation_ = { 0.0f, y + worldTransform_.scale_.y, 0.0f };//{0.0,7.5,0.0}

	Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();

	debugText_ = DebugText::GetInstance();
}

void Core::Update(WorldTransform worldTransform, WorldTransform* wall, bool* collision)
{
	//コアがステージの上にある時	
	if (worldTransform_.matWorld_.m[3][0] < worldTransform.scale_.x && worldTransform_.matWorld_.m[3][0] > -worldTransform.scale_.x &&
		worldTransform_.matWorld_.m[3][2] < worldTransform.scale_.z && worldTransform_.matWorld_.m[3][2] > -worldTransform.scale_.z) {
		//速度を0にする
		velocity_.y = 0;

	}
	else {
		for (int i = 0; i < totalBlockNum; i++) {
			//壁に当たったら
			if (collision[i]) {
				//位置を少し戻し、速度を0にする
				isFall = 0;
				worldTransform_.matWorld_.m[3][1] -= velocity_.y;
				velocity_.y = 0.0f;
			}
		}
		//ステージが回転していないとき
		if ((worldTransform.rotation_.x != 0.0f || worldTransform.rotation_.z != 0.0f) && isFall)
		{
			//一定まで加速し続ける
			if (velocity_.y <= 0.5f)
			{
				velocity_.y -= 0.01f;
			}
		}
	}

	//一番下まで行ったら止まる
	if (worldTransform_.matWorld_.m[3][1] < -(worldTransform.scale_.y+0.5f))
	{
		velocity_.y = 0.0f;
		worldTransform_.matWorld_.m[3][1] = -(worldTransform.scale_.y + 0.5f);
		
	}

	//アフィン変換
	worldTransform_.translation_ += velocity_;
	Affine::CreateMatTrans(worldTransform_, { velocity_.x,velocity_.y,velocity_.z });
	worldTransform_.TransferMatrix();

}

void Core::Draw(ViewProjection* viewProjection)
{
	coreModel_->Draw(worldTransform_, *viewProjection, textureHandle_);
}

void Core::SetWorldTransform(WorldTransform worldTransform)
{
	Affine::CreateMatRotZ(worldTransform_, worldTransform.rotation_);
	Affine::CreateMatRotX(worldTransform_, worldTransform.rotation_);
	worldTransform_.TransferMatrix();
}
