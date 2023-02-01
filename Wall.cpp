#include "Wall.h"

Wall::~Wall() {
	delete model_;
}

void Wall::Initialize() {

	//���f�����蓖��
	model_ = Model::LoadFromOBJ("woodCube");

	//�S���[���h�s�񏉊���
	for (int i = 0; i < totalBlockNum; i++) {
		wallObject[i].Initialize();
		wallObject[i].SetModel(model_);
		wallObject[i].scale = { blockSize,blockSize,blockSize };
		//wallObject[0].SetPosition({ 2.0f,11.0f,0.0f });
		wallObject[i].Update();
		wallObject[i].TransferMatrix();

	}

	SetBlock();
}

void Wall::SetBlock() {
	//�}�b�v�`�b�v�ʂ�ɕǃu���b�N��z�u
	int num = 0;
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			//wallObject[num].Initialize();

			mapTop[j][i] = map1Top[j][i];
			mapRight[j][i] = map1Right[j][i];
			mapLeft[j][i] = map1Left[j][i];
			mapFront[j][i] = map1Front[j][i];
			mapBehind[j][i] = map1Behind[j][i];
			mapBottom[j][i] = map1Bottom[j][i];

			//��
			if (mapTop[j][i] == 1) {
				wallObject[num].position = {
					-stageSize + i * wallObject->scale.x * 2,
					stageSize,
					stageSize - j * wallObject->scale.z * 2,
				};
			}
			//�E
			if (mapRight[j][i] == 1) {
				wallObject[num + oneSideBlockNum * 1].position = {
					stageSize,
					stageSize - i * wallObject->scale.y * 2,
					stageSize - j * wallObject->scale.z * 2
				};
			}
			//��
			if (mapLeft[j][i] == 1) {
				wallObject[num + oneSideBlockNum * 2].position = {
					-stageSize,
					-stageSize + i * wallObject->scale.y * 2,
					stageSize - j * wallObject->scale.z * 2,
				};
			}
			//�O
			if (mapFront[j][i] == 1) {
				wallObject[num + oneSideBlockNum * 3].position = {
					-stageSize + i * wallObject->scale.y * 2,
					stageSize - j * wallObject->scale.z * 2,
					-stageSize,
				};
			}
			//��
			if (mapBehind[j][i] == 1) {
				wallObject[num + oneSideBlockNum * 4].position = {
					-stageSize + i * wallObject->scale.y * 2,
					stageSize - j * wallObject->scale.z * 2,
					stageSize,
				};
			}
			//��
			if (mapBottom[j][i] == 1) {
				wallObject[num + oneSideBlockNum * 5].position = {
					-stageSize + i * wallObject->scale.y * 2,
					-stageSize,
					stageSize - j * wallObject->scale.z * 2,
				};
			}

			num++;
		}
	}

	for (int i = 0; i < totalBlockNum; i++) {
		wallObject[i].SetPosition(wallObject[i].position);
		wallObject[i].Update();
		wallObject[i].TransferMatrix();
	}
}

void Wall::Draw() {
	for (int i = 0; i < totalBlockNum; i++) {
		if (wallObject[i].position.y != 0.0f) {
			wallObject[i].Draw();
		}
	}
}

void Wall::Rotate(Object3d* obj) {
	for (int i = 0; i < totalBlockNum; i++) {
		wallObject[i].CreateMatRotZ(obj->rotation);
		wallObject[i].CreateMatRotX(obj->rotation);
		wallObject[i].TransferMatrix();
	}
}