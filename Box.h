#pragma once
#include "GameObject3D.h"
#include "MathFunc.h"

class Box {
public:	//�����o�֐�
	//�C���X�g���N�^
	Box();
	//�f�X�g���N�^
	~Box();

	//������
	void Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection);
	//���f���ǂݍ���
	void GetModel();
	//�X�V
	void Update();
	//�`��
	void Draw();

private:	//�����o�ϐ�

	//�X�e�[�W
	GameObject3D* field = nullptr;
};
