#include "GameScene.h"
//#include "Affine.h"

void GameScene::Initialize() {
	//�R���\�[���ւ̕����o��
	/*�R���\�[���E�E�E�L�`�Ńp�\�R���S�ʂ̓��́E�o�͗p�̑��u�̂��Ƃ��w���A��ɃL�[�{�[�h��f�B�X�v���C�̂���*/
	//OutputDebugStringA("Hello,DirectX!!\n");

	//WindowsAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();

	//DirectX���������� ��������
	/*DirectX�E�E�E�}�C�N���\�t�g���J�������Q�[���E�}���`���f�B�A�����p��API�̏W��*/
	/*API�E�E�EApplication Programming Interface�̗�
	�\�t�g�E�F�A����OS�̋@�\�𗘗p���邽�߂̎d�l�܂��̓C���^�[�t�F�[�X(���҂̊Ԃŏ���M���Ȃǂ����Ƃ肷�邽�߂̎菇��K����߂�����)�̑���
	�A�v���P�[�V�����̊J����e�Ղɂ��邽�߂̃\�t�g�E�F�A�����̂��Ƃ�����*/
	//HRESULT result;

	//DirectX�̏�����
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//���͂̏�����
	input = new Input();
	input->Initialize(winApp);

	//3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	//�`�揉������������

	//�X�v���C�g���ʕ��̏�����
	spriteCommon = new SpriteCommon();
	spriteCommon->Initialize(dxCommon);

	//�e�N�X�`���ǂݍ���
	spriteCommon->LoadTexture(1, "reimu.png");
	spriteCommon->LoadTexture(0, "mario.jpg");

	sprite->Initialize(spriteCommon);
	sprite1->Initialize(spriteCommon);

	object3d = Object3d::Create();
	//object3d2 = Object3d::Create();
	model = Model::LoadFromOBJ("cube");
	model2 = Model::LoadFromOBJ("triangle_mat");
	//�I�u�W�F�N�g�Ƀ��f�����Ђ��Â���
	object3d->SetModel(model);
	//object3d2->SetModel(model2);

	//�v���C���[�̐���
	//player_ = new Player();
	//player_->Initialize(0.0f);

	Object3d::SetEye({ 15.0f,20.0f,-20.0f });
	Object3d::SetTarget({0, 0, 0});
	//viewProjection_.Initialize();
	//viewProjection_.eye = { 0.0f,0.0f,-50.0f };
	//viewProjection_.UpdateView();
	//Affine::CreateAffine(worldTransform_);
	object3d->Update();

	//worldTransform_.UpdateMatWorld();
	//worldTransform_.Initialize();
	//worldTransform_.scale_ = { 7.0f,7.0f,7.0f };
	//worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
	//Affine::CreateAffine(worldTransform_);

	//worldTransform_.UpdateMatWorld();
}

void GameScene::Finalize() {
	//WindowsAPI�̏I������
	winApp->Finalize();

	//�X�v���C�g���
	delete sprite;
	delete sprite1;
	delete spriteCommon;
	//3D�I�u�W�F�N�g���
	delete object3d;
	//delete object3d2;
	//3D���f�����
	delete model;
	delete model2;
	//delete player_;
	//DirectX���
	delete dxCommon;
	//���͉��
	delete input;
	//WindowsAPI���
	delete winApp;

}

void GameScene::Update() {
	

	//DirectX���t���[������ ��������

	//���͂̍X�V
	input->Update();
	//sprite->Update(spriteCommon);

	if (input->PushKey(DIK_A)) {
		object3d->rotation.z = 1.0f;
		object3d->CreateMatRotZ(object3d->rotation);

	}
	else if (input->PushKey(DIK_D)) {
		object3d->rotation.z = -1.0f;
		object3d->CreateMatRotZ(object3d->rotation);
	}

	//Affine::CreateMatRotZ(object3d->matWorld, object3d->rotation);

	if (input->PushKey(DIK_W)) {
		object3d->CreateMatRotX(object3d->rotation);
		object3d->rotation.x = 1.0f;
	}
	else if (input->PushKey(DIK_S)) {
		object3d->CreateMatRotX(object3d->rotation);
		object3d->rotation.x = -1.0f;
	}

	//player_->SetRotation(rotation);
	//worldTransform_.UpdateMatWorld();

	//3D�I�u�W�F�N�g�X�V
	//object3d->SetPosition({ -10.0f,0.0f,0.0f });
	//object3d2->SetPosition({ 10.0f,0.0f,0.0f });
	//object3d2->Update();
	//player_->Update();

	//viewProjection_.UpdateView();
	//worldTransform_.UpdateMatWorld();
}

void GameScene::Draw() {
	//�`��O����
	dxCommon->PreDraw();

	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());

	//3D�I�u�W�F�N�g�̕`��
	object3d->Draw();
	//object3d2->Draw();
	//player_->Draw();
	//3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	//�X�v���C�g�`��O����
	spriteCommon->PreDraw();

	////�`��R�}���h��������
	spriteCommon->Update(dxCommon);
	//sprite->SetPosition(position);
	sprite1->SetPosition({ 100.0f,100.0f });
	sprite->SetIndex(0);
	sprite1->SetIndex(1);
	//sprite1->SetTextureSize({ 500.0f,450.0f });

	sprite->Draw(spriteCommon);
	sprite1->Draw(spriteCommon);
	////�`��R�}���h�����܂�

	//�X�v���C�g�`��㏈��
	spriteCommon->PostDraw();


	dxCommon->PostDraw();


	//DirectX���t���[������ �����܂�
}