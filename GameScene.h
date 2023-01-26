#pragma once
//#include "WinApp.h"
#include "Object3d.h"
#include "Sprite.h"
#include "Input.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
//#include "Player.h"

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

	WinApp* GetWinApp() { return winApp; }

private:
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
	//3D�I�u�W�F�N�g����
	Object3d* object3d = nullptr;
	//Object3d* object3d2 = nullptr;
	//WorldTransform worldTransform_;
	//ViewProjection viewProjection_;
	//Player* player_ = nullptr;

};

