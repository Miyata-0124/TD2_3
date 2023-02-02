#include "Core.h"
#include "map.h"
Core::~Core() {
	delete coreModel_;
	delete leadModel_;
	delete coreObject_;
}
void Core::Initialize(float y)
{

	coreModel_ = Model::LoadFromOBJ("Core");
	coreObject_ = Object3d::Create();
	coreObject_->SetModel(coreModel_);
	coreObject_->position = { 0.0f,y+1.0f,0.0f };
	coreObject_->SetPosition(coreObject_->position);
	coreObject_->SetScale({ 1.0f,1.0f,1.0f });
	coreObject_->Update();
	/*textureHandle_ = TextureManager::Load("Core.png");
	coreModel_ = Model::Create();*/
	//worldTransform_.Initialize();
	//worldTransform_.scale_ = { 0.5f,0.5f,0.5f };
	//worldTransform_.translation_ = { 0.0f, y + worldTransform_.scale_.y, 0.0f };//{0.0,7.5,0.0}
	/*Affine::CreateAffine(worldTransform_);
	worldTransform_.TransferMatrix();*/
	for (int i = 0; i < leadNum; i++) {
		leadWorldTransformsX_[i].Initialize();
		leadWorldTransformsY_[i].Initialize();
		leadWorldTransformsZ_[i].Initialize();

		leadWorldTransformsX_[i].scale = { scale,scale,scale };
		leadWorldTransformsY_[i].scale = { scale,scale,scale };
		leadWorldTransformsZ_[i].scale = { scale,scale,scale };

		leadWorldTransformsX_[i].SetModel(leadModel_);
		leadWorldTransformsY_[i].SetModel(leadModel_);
		leadWorldTransformsZ_[i].SetModel(leadModel_);
		/*leadWorldTransformsX_[i % 30].position =
		{
			-leadNum / 6.0f + i,
			coreObject_->matWorld.r[3].m128_f32[1],
			coreObject_->matWorld.r[3].m128_f32[2]
		};
		leadWorldTransformsX_[(30 + i) % 60].position =
		{
			coreObject_->matWorld.r[3].m128_f32[0],
			-leadNum / 6.0f + i,
			coreObject_->matWorld.r[3].m128_f32[2]
		};
		if (i < leadNum / 3 * 1) {
		}
		if (i >= 30 && i < 60) {
		}*/

		leadWorldTransformsX_[i].position =
		{
			-leadNum / 2.0f + i,
			coreObject_->matWorld.r[3].m128_f32[1],
			coreObject_->matWorld.r[3].m128_f32[2]
		};
		leadWorldTransformsY_[i].position =
		{
			coreObject_->matWorld.r[3].m128_f32[0],
			-leadNum / 2.0f + i,
			coreObject_->matWorld.r[3].m128_f32[2]
		};
		leadWorldTransformsZ_[i].position =
		{
			coreObject_->matWorld.r[3].m128_f32[0],
			coreObject_->matWorld.r[3].m128_f32[1],
			-leadNum / 2.0f + i
		};
		leadWorldTransformsX_[i].Update();
		leadWorldTransformsY_[i].Update();
		leadWorldTransformsZ_[i].Update();
		leadWorldTransformsX_[i].TransferMatrix();
		leadWorldTransformsY_[i].TransferMatrix();
		leadWorldTransformsZ_[i].TransferMatrix();
		}
}

void Core::Update(Object3d* obj, bool *collision)
{
	//コアがステージの上にある時
	if (coreObject_->matWorld.r[3].m128_f32[0] < obj->scale.x && coreObject_->matWorld.r[3].m128_f32[0] > -obj->scale.x &&
		coreObject_->matWorld.r[3].m128_f32[2]  < obj->scale.z && coreObject_->matWorld.r[3].m128_f32[2] > -obj->scale.z) {
		//速度を0にする
		velocity_.y = 0;
	}
	else {
		for (int i = 0; i < totalBlockNum; i++) {
			//壁に当たったら
			if (collision[i]) {
				//位置を少し戻し、速度を0にする
				isFall = 0;

				coreObject_->matWorld.r[3].m128_f32[1] -= velocity_.y - 0.1f ;
        
				velocity_.y = 0.0f;
			}
		}
		//ステージが回転していないとき
		if ((obj->rotation.x != 0.0f || obj->rotation.z != 0.0f) && isFall)
		{
			//一定まで加速し続ける
			if (velocity_.y <= 0.5f && coreObject_->matWorld.r[3].m128_f32[1] > -obj->scale.y)
			{
				velocity_.y -= 0.01f;
			}
		}
	}
	//一番下まで行ったら止まる
	if (coreObject_->matWorld.r[3].m128_f32[1] < -(obj->scale.y + 1.0f))
	{
		velocity_.y = 0.0f;
		coreObject_->matWorld.r[3].m128_f32[1] = -(obj->scale.y + 1.0f);
	}

	coreObject_->position.y += velocity_.y;
	coreObject_->CreateMatTrans(velocity_);
	coreObject_->TransferMatrix();

	//指標のアフィン変換
	for (int i = 0; i < leadNum; i++) {

		if ((leadWorldTransformsX_[0].matWorld.r[3].m128_f32[1] - leadWorldTransformsX_[10].matWorld.r[3].m128_f32[1]) < 2.0f &&
			(leadWorldTransformsX_[0].matWorld.r[3].m128_f32[1] - leadWorldTransformsX_[10].matWorld.r[3].m128_f32[1]) > -2.0f) {

			leadWorldTransformsX_[i].matWorld.r[3].m128_f32[1] = coreObject_->matWorld.r[3].m128_f32[1];
			leadWorldTransformsX_[i].CreateMatTrans({ velocity_.x,velocity_.y,velocity_.z });
			//leadWorldTransformsX_[i].CreateMatRotX(coreObject_->rotation);
			//leadWorldTransformsX_[i].TransferMatrix();
		}
		if ((leadWorldTransformsY_[0].matWorld.r[3].m128_f32[1] - leadWorldTransformsY_[10].matWorld.r[3].m128_f32[1]) < 2.0f &&
			(leadWorldTransformsY_[0].matWorld.r[3].m128_f32[1] - leadWorldTransformsY_[10].matWorld.r[3].m128_f32[1]) > -2.0f) {

			leadWorldTransformsY_[i].matWorld.r[3].m128_f32[1] = coreObject_->matWorld.r[3].m128_f32[1];
			leadWorldTransformsY_[i].CreateMatTrans({ velocity_.x,velocity_.y,velocity_.z });
			//leadWorldTransformsY_[i].CreateMatRotY(coreObject_->rotation);
			leadWorldTransformsY_[i].TransferMatrix();
		}
		if ((leadWorldTransformsZ_[0].matWorld.r[3].m128_f32[1] - leadWorldTransformsZ_[10].matWorld.r[3].m128_f32[1]) < 2.0f &&
			(leadWorldTransformsZ_[0].matWorld.r[3].m128_f32[1] - leadWorldTransformsZ_[10].matWorld.r[3].m128_f32[1]) > -2.0f) {

			leadWorldTransformsZ_[i].matWorld.r[3].m128_f32[1] = coreObject_->matWorld.r[3].m128_f32[1];
			leadWorldTransformsZ_[i].CreateMatTrans({ velocity_.x,velocity_.y,velocity_.z });
			//leadWorldTransformsZ_[i].CreateMatRotZ(coreObject_->rotation);
			leadWorldTransformsZ_[i].TransferMatrix();
		}

	}

}
void Core::Draw()
{
	coreObject_->Draw();
	for (int i = 0; i < leadNum; i++) {
		leadWorldTransformsX_[i].Draw();
		leadWorldTransformsY_[i].Draw();
		leadWorldTransformsZ_[i].Draw();
	}
}
void Core::Rotate(Object3d* obj)
{
	coreObject_->CreateMatRotZ(obj->rotation);
	coreObject_->CreateMatRotY(obj->rotation);
	coreObject_->CreateMatRotX(obj->rotation);
	coreObject_->TransferMatrix();

		for (int i = 0; i < leadNum; i++) {
			leadWorldTransformsX_[i].CreateMatRotZ(obj->rotation);
			leadWorldTransformsX_[i].CreateMatRotX(obj->rotation);
			leadWorldTransformsX_[i].TransferMatrix();
			leadWorldTransformsY_[i].CreateMatRotZ(obj->rotation);
			leadWorldTransformsY_[i].CreateMatRotX(obj->rotation);
			leadWorldTransformsY_[i].TransferMatrix();
			leadWorldTransformsZ_[i].CreateMatRotZ(obj->rotation);
			leadWorldTransformsZ_[i].CreateMatRotX(obj->rotation);
			leadWorldTransformsZ_[i].TransferMatrix();
	}
}
//void Core::SetWorldTransform(WorldTransform worldTransform)
//{
//	Affine::CreateMatRotZ(worldTransform_, worldTransform.rotation_);
//	Affine::CreateMatRotX(worldTransform_, worldTransform.rotation_);
//	worldTransform_.TransferMatrix();
//
//	for (int i = 0; i < leadNum; i++) {
//		Affine::CreateMatRotZ(leadWorldTransformsX_[i], worldTransform.rotation_);
//		Affine::CreateMatRotX(leadWorldTransformsX_[i], worldTransform.rotation_);
//		leadWorldTransformsX_[i].TransferMatrix();
//		Affine::CreateMatRotZ(leadWorldTransformsY_[i], worldTransform.rotation_);
//		Affine::CreateMatRotX(leadWorldTransformsY_[i], worldTransform.rotation_);
//		leadWorldTransformsY_[i].TransferMatrix();
//		Affine::CreateMatRotZ(leadWorldTransformsZ_[i], worldTransform.rotation_);
//		Affine::CreateMatRotX(leadWorldTransformsZ_[i], worldTransform.rotation_);
//		leadWorldTransformsZ_[i].TransferMatrix();
//	}
//}