#include "Wall.h"
#include "Affine.h"

Wall::~Wall() {
	delete model_;
}

void Wall::Initialize() {

	//モデル割り当て
	model_ = Model::CreateFromOBJ("cube", true);

	//全ワールド行列初期化
	for (int i = 0; i < totalBlockNum; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].scale_ = { blockSize,blockSize,blockSize };
	}

	//マップチップ通りに壁ブロックを配置
	int num = 0;
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			worldTransform_[num].Initialize();

			//上
			top[j][i] = mapTop[j][i];
			if (top[j][i] == 1) {
				worldTransform_[num].translation_ = {
					-8.0f + i * worldTransform_->scale_.x * 2,
					8.0f,
					8.0f - j * worldTransform_->scale_.z * 2,
				};
			}
			//右
			if (mapRight[j][i] == 1) {
				worldTransform_[num + oneSideBlockNum * 1].translation_ = {
					8.0f,
					8.0f - i * worldTransform_->scale_.y * 2,
					8.0f - j * worldTransform_->scale_.z * 2
				};
			}
			//左
			if (mapLeft[j][i] == 1) {
				worldTransform_[num + oneSideBlockNum * 2].translation_ = {
					-8.0f,
					-8.0f + i * worldTransform_->scale_.y * 2,
					8.0f - j * worldTransform_->scale_.z * 2,
				};
			}
			//前
			if (mapFront[j][i] == 1) {
				worldTransform_[num + oneSideBlockNum * 3].translation_ = {
					-8.0f + i * worldTransform_->scale_.y * 2,
					8.0f - j * worldTransform_->scale_.z * 2,
					-8.0f,
				};
			}
			//後
			if (mapBehind[j][i] == 1) {
				worldTransform_[num + oneSideBlockNum * 4].translation_ = {
					-8.0f + i * worldTransform_->scale_.y * 2,
					8.0f - j * worldTransform_->scale_.z * 2,
					8.0f,
				};
			}
			//下
			if (mapBottom[j][i] == 1) {
				worldTransform_[num + oneSideBlockNum * 5].translation_ = {
					-8.0f + i * worldTransform_->scale_.y * 2,
					-8.0f,
					8.0f - j * worldTransform_->scale_.z * 2,
				};
			}

			num++;
		}
	}

	//アフィン変換＆行列更新
	for (int i = 0; i < totalBlockNum; i++) {
		Affine::CreateAffine(worldTransform_[i]);
		worldTransform_[i].TransferMatrix();
	}
}

void Wall::Rotate(WorldTransform worldTransform) {
	for (WorldTransform& worldTransform_ : worldTransform_) {
		Affine::CreateMatRotZ(worldTransform_, worldTransform.rotation_);
		Affine::CreateMatRotX(worldTransform_, worldTransform.rotation_);

		worldTransform_.TransferMatrix();
	}
}

void Wall::Draw(ViewProjection* viewProjection) {
	for (WorldTransform& worldTransform_ : worldTransform_) {
		model_->Draw(worldTransform_, *viewProjection);
	}
}

WorldTransform* Wall::GetWorldTransform() {
	return worldTransform_;
}