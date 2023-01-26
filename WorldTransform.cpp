#include "WorldTransform.h"

void WorldTransform::Initialize() {

	scale_ = { 1 , 1 , 1 };
	rotation_ = { 0 , 0 , 0 };
	translation_ = { 0 , 0 , 0 };
	matWorld_.SetIdentityMatrix();

	UpdateMatWorld();

}

//���[���h�ϊ��s��̍X�V
void WorldTransform::UpdateMatWorld() {

	//���[���h�ϊ��s���p��
	Matrix4 affineMat;
	affineMat.SetIdentityMatrix();

	////���[���h�ϊ��s��ɃX�P�[�����O,��],���s�ړ��̍s�������
	MathFunc::Affine::SetMatScale(affineMat, scale_);
	MathFunc::Affine::SetMatRotation(affineMat, rotation_);
	MathFunc::Affine::SetMatTranslation(affineMat, translation_);

	////���[���h�s��ɒP�ʍs�����
	matWorld_.SetIdentityMatrix();

	//�s��̌v�Z
	matWorld_ *= affineMat;

	//�����e������ꍇ
	if (parent) {
		//�e�̃��[���h�s��Ƃ̌v�Z���s��
		matWorld_ *= parent->matWorld_;
	}

}