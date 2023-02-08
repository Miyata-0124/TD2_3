#pragma once
#include "map.h"
#include "Object3d.h"
#include "Sprite.h"
#include "Input.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "ViewProjection.h"
#include "Player.h"
#include "Wall.h"
#include "Core.h"
#include "Goal.h"

class GameScene
{
public:

	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update();
	//�`��
	void Draw();

	//�����蔻��
	bool CheakCollision(XMFLOAT3 posA, XMFLOAT3 posB, XMFLOAT3 sclA, XMFLOAT3 sclB);

	WinApp* GetWinApp() { return winApp; }

	//�C�[�W���O
	float easeOutSine(float n) {
		return 1 - pow(1 - n, 2);
	}

private:
	const float PI = 3.14159f;

	//�|�C���^
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;

	//�X�v���C�g���ʕ��̃|�C���^
	SpriteCommon* spriteCommon = nullptr;

	Sprite* sprite = new Sprite();
	Sprite* sprite1 = new Sprite();

	//OBJ���烂�f���f�[�^��ǂݍ���
	Model* model = nullptr;
	Model* model2 = nullptr;
	Model* model3 = nullptr;
	Model* skydomeModel = nullptr;
	//3D�I�u�W�F�N�g����
	Object3d* stageObject = nullptr;
	Object3d* taitleObject = nullptr;
	Object3d* skydomeObject = nullptr;
	//Object3d* object3d2 = nullptr;
	//WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Player* player_ = nullptr;
	Core* core_ = nullptr;
	Wall* wall_ = nullptr;
	Goal* goal_ = nullptr;

	int scene = 0;
	int isRotateZ = 0;
	int isRotateX = 0;
	float rotateTimer = 0.0f;
	const float radian = 2.0f;

	XMFLOAT3 wallCollisions[totalBlockNum];
	bool isHitPlayer[totalBlockNum] = { 0 };
	bool isHitCore[totalBlockNum] = { 0 };
	bool isHitGoal = 0;
	bool isFall = 1;
	int cameraPosition = 0;

	//�ő�t���[����
	const float MAX_FLAME = 0.1f;
};