#include "Wall.h"

Wall::~Wall() {
	delete model_;
}

void Wall::Initialize() {

	//�S���[���h�s�񏉊���
	for (int i = 0; i < totalBlockNum; i++) {
		wallObject[i].Initialize();
		wallObject[i].SetModel(model_);
		wallObject[i].scale = { blockSize,blockSize,blockSize };
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

			if (stageNum == 1) {//�X�e�[�W1
				mapTop[j][i] = map1Top[j][i];
				mapRight[j][i] = map1Right[j][i];
				mapLeft[j][i] = map1Left[j][i];
				mapFront[j][i] = map1Front[j][i];
				mapBehind[j][i] = map1Behind[j][i];
				mapBottom[j][i] = map1Bottom[j][i];
			}
			else if (stageNum == 2) {//�X�e�[�W2
				mapTop[j][i] = map2Top[j][i];
				mapRight[j][i] = map2Right[j][i];
				mapLeft[j][i] = map2Left[j][i];
				mapFront[j][i] = map2Front[j][i];
				mapBehind[j][i] = map2Behind[j][i];
				mapBottom[j][i] = map2Bottom[j][i];
			}
			else if (stageNum == 3) {//�X�e�[�W3
				mapTop[j][i] = map3Top[j][i];
				mapRight[j][i] = map3Right[j][i];
				mapLeft[j][i] = map3Left[j][i];
				mapFront[j][i] = map3Front[j][i];
				mapBehind[j][i] = map3Behind[j][i];
				mapBottom[j][i] = map3Bottom[j][i];
			}

			//��
			if (mapTop[j][i] == 1) {
				wallObject[num].position = {
					-stageSize + i * wallObject->scale.x * 2,
					stageSize,
					stageSize - j * wallObject->scale.z * 2,
				};
			}
			else if (mapTop[j][i] == 0) {
				wallObject[num].position = { 0.0f,0.0f,0.0f };
			}
			//�E
			if (mapRight[j][i] == 1) {
				wallObject[num + oneSideBlockNum * 1].position = {
					stageSize,
					stageSize - i * wallObject->scale.y * 2,
					stageSize - j * wallObject->scale.z * 2
				};
			}
			else {
				wallObject[num + oneSideBlockNum * 1].position = { 0.0f,0.0f,0.0f };
			}
			//��
			if (mapLeft[j][i] == 1) {
				wallObject[num + oneSideBlockNum * 2].position = {
					-stageSize,
					-stageSize + i * wallObject->scale.y * 2,
					stageSize - j * wallObject->scale.z * 2,
				};
			}
			else {
				wallObject[num + oneSideBlockNum * 2].position = { 0.0f,0.0f,0.0f };
			}
			//�O
			if (mapFront[j][i] == 1) {
				wallObject[num + oneSideBlockNum * 3].position = {
					-stageSize + i * wallObject->scale.y * 2,
					stageSize - j * wallObject->scale.z * 2,
					-stageSize,
				};
			}
			else {
				wallObject[num + oneSideBlockNum * 3].position = { 0.0f,0.0f,0.0f };
			}
			//��
			if (mapBehind[j][i] == 1) {
				wallObject[num + oneSideBlockNum * 4].position = {
					-stageSize + i * wallObject->scale.y * 2,
					stageSize - j * wallObject->scale.z * 2,
					stageSize,
				};
			}
			else {
				wallObject[num + oneSideBlockNum * 4].position = { 0.0f,0.0f,0.0f };
			}
			//��
			if (mapBottom[j][i] == 1) {
				wallObject[num + oneSideBlockNum * 5].position = {
					-stageSize + i * wallObject->scale.y * 2,
					-stageSize,
					stageSize - j * wallObject->scale.z * 2,
				};
			}
			else {
				wallObject[num + oneSideBlockNum * 5].position = { 0.0f,0.0f,0.0f };
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
		wallObject[i].CreateMatRotY(obj->rotation);
		wallObject[i].CreateMatRotX(obj->rotation);
		wallObject[i].TransferMatrix();
	}
}