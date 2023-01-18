#include "Wall.h"
#include "Affine.h"

Wall::~Wall() {
	delete wallModel_;
}

void Wall::Initialize() {

	//���f�����蓖��
	wallModel_ = Model::LoadFromOBJ("cube");
	wallObject_ = GameObject3D::Create();
	wallObject_->SetModel(wallModel_);
	//�S���[���h�s�񏉊���
	for (int i = 0; i < totalBlockNum; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].scale_ = { blockSize,blockSize,blockSize };
	}

	SetBlock();
}

void Wall::SetBlock() {
	//�}�b�v�`�b�v�ʂ�ɕǃu���b�N��z�u
	int num = 0;
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			worldTransform_[num].Initialize();

			//��
			top[j][i] = mapTop[j][i];
			if (top[j][i] == 1) {
				worldTransform_[num].translation_ = {
					-8.0f + i * worldTransform_->scale_.x * 2,
					8.0f,
					8.0f - j * worldTransform_->scale_.z * 2,
				};
			}
			//�E
			if (mapRight[j][i] == 1) {
				worldTransform_[num + oneSideBlockNum * 1].translation_ = {
					8.0f,
					8.0f - i * worldTransform_->scale_.y * 2,
					8.0f - j * worldTransform_->scale_.z * 2
				};
			}
			//��
			if (mapLeft[j][i] == 1) {
				worldTransform_[num + oneSideBlockNum * 2].translation_ = {
					-8.0f,
					-8.0f + i * worldTransform_->scale_.y * 2,
					8.0f - j * worldTransform_->scale_.z * 2,
				};
			}
			//�O
			if (mapFront[j][i] == 1) {
				worldTransform_[num + oneSideBlockNum * 3].translation_ = {
					-8.0f + i * worldTransform_->scale_.y * 2,
					8.0f - j * worldTransform_->scale_.z * 2,
					-8.0f,
				};
			}
			//��
			if (mapBehind[j][i] == 1) {
				worldTransform_[num + oneSideBlockNum * 4].translation_ = {
					-8.0f + i * worldTransform_->scale_.y * 2,
					8.0f - j * worldTransform_->scale_.z * 2,
					8.0f,
				};
			}
			//��
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

	//�A�t�B���ϊ����s��X�V
	for (int i = 0; i < totalBlockNum; i++) {
		Affine::CreateAffine(worldTransform_[i]);
		worldTransform_[i].UpdateMatWorld();
	}
}

void Wall::Rotate(WorldTransform worldTransform) {
	for (WorldTransform& worldTransform_ : worldTransform_) {
		Affine::CreateMatRotZ(worldTransform_, worldTransform.rotation_);
		Affine::CreateMatRotX(worldTransform_, worldTransform.rotation_);

		worldTransform_.UpdateMatWorld();
	}
}

void Wall::Draw(ViewProjection* viewProjection) {
	for (WorldTransform& worldTransform_ : worldTransform_) {
		wallObject_->Draw();
	}
}

WorldTransform* Wall::GetWorldTransform() {
	return worldTransform_;
}