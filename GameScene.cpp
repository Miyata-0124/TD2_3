#include "GameScene.h"
//#include "Affine.h"

void GameScene::Initialize() {
	//�R���\�[���ւ̕����o��
	//�R���\�[���E�E�E�L�`�Ńp�\�R���S�ʂ̓��́E�o�͗p�̑��u�̂��Ƃ��w���A��ɃL�[�{�[�h��f�B�X�v���C�̂���
	//OutputDebugStringA("Hello,DirectX!!\n");

	//WindowsAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();

	//DirectX���������� ��������
	//DirectX�E�E�E�}�C�N���\�t�g���J�������Q�[���E�}���`���f�B�A�����p��API�̏W��
	//API�E�E�EApplication Programming Interface�̗�
	//�\�t�g�E�F�A����OS�̋@�\�𗘗p���邽�߂̎d�l�܂��̓C���^�[�t�F�[�X(���҂̊Ԃŏ���M���Ȃǂ����Ƃ肷�邽�߂̎菇��K����߂�����)�̑���
	//�A�v���P�[�V�����̊J����e�Ղɂ��邽�߂̃\�t�g�E�F�A�����̂��Ƃ�����
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

	//�J�����̏�����
	Object3d::SetEye({ 14.5f,23.0f,-14.5f });
	Object3d::SetTarget({ 1, 0, -1 });

	//�X�v���C�g���ʕ��̏�����
	spriteCommon = new SpriteCommon();
	spriteCommon->Initialize(dxCommon);

	//�e�N�X�`���ǂݍ���
	spriteCommon->LoadTexture(1, "reimu.png");
	spriteCommon->LoadTexture(0, "mario.jpg");

	sprite->Initialize(spriteCommon);
	sprite1->Initialize(spriteCommon);

	stageObject = Object3d::Create();
	//object3d2 = Object3d::Create();
	model = Model::LoadFromOBJ("cube");
	model2 = Model::LoadFromOBJ("triangle_mat");
	//�I�u�W�F�N�g�Ƀ��f�����Ђ��Â���
	stageObject->SetModel(model);
	//object3d2->SetModel(model2);

	stageObject->SetScale({ 10.0f,10.0f,10.0f });

	//�v���C���[�̐���
	player_ = new Player();
	player_->Initialize(0.0f);
	//�R�A�̐���
	core_ = new Core();
	core_->Initialize(stageObject->scale.y);
	//�S�[���̐���
	goal_ = new Goal();
	goal_->Initialize(stageObject->scale.y);
	//�ǃu���b�N�̐���
	wall_ = new Wall();
	wall_->Initialize();

	viewProjection_.Initialize();
	viewProjection_.eye = { 20.0f,20.0f,-30.0f };
	viewProjection_.UpdateView();
	//Affine::CreateAffine(worldTransform_);
	stageObject->Update();

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
	delete stageObject;
	//delete object3d2;
	//3D���f�����
	delete model;
	delete model2;
	delete player_;
	delete core_;
	delete wall_;
	delete goal_;
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
	if (input->PushKey(DIK_UP)) {
		viewProjection_.eye.y += 2.5f;
		if (viewProjection_.eye.y > 50)
		{
			viewProjection_.eye.y = -0.01;
			viewProjection_.eye.z = -0.01;
		}
	}
	else {
		viewProjection_.eye = { 0, 0, -50 };
		viewProjection_.target = { 0, 0, 0 };
	}
	if (input->PushKey(DIK_LEFT)) {
		viewProjection_.eye = { -50, 0, 0 };
	}
	if (input->PushKey(DIK_DOWN)) {
		viewProjection_.eye = { 0, -50, -0.01 };
	}
	if (input->PushKey(DIK_RIGHT)) {
		viewProjection_.eye = { 50, 0, 0 };
	}
	viewProjection_.UpdateView();
	switch (scene)
	{
	case 0:// �^�C�g��
		if (input->PushKey(DIK_SPACE)) {
			scene = 1;
		}
		break;
	case 1:// �Q�[���v���C
#pragma region �Q�[���v���C
		/*�����蔻��֘A*/
//�v���C���[�̈ʒu���Ƃ�
		XMFLOAT3 playerCollision =
		{
			player_->GetTransform()->matWorld.r[3].m128_f32[0],
			player_->GetTransform()->matWorld.r[3].m128_f32[1],
			player_->GetTransform()->matWorld.r[3].m128_f32[2],
		};

		XMFLOAT3 coreCollision =
		{
			core_->GetTransform()->matWorld.r[3].m128_f32[0],
			core_->GetTransform()->matWorld.r[3].m128_f32[1],
			core_->GetTransform()->matWorld.r[3].m128_f32[2],
		};

		for (int i = 0; i < totalBlockNum; i++) {

			//�ǃu���b�N�̈ʒu���Ƃ�
			wallCollisions[i] =
			{
				wall_->GetTransform()[i].matWorld.r[3].m128_f32[0],
				wall_->GetTransform()[i].matWorld.r[3].m128_f32[1],
				wall_->GetTransform()[i].matWorld.r[3].m128_f32[2],
			};

			//�S�Ă̕ǃu���b�N�ƃv���C���[�̓����蔻����Ƃ�
			if (CheakCollision(
				wallCollisions[i], playerCollision,
				wall_->GetScale(), player_->GetScale())) {
				isHitPlayer[i] = 1;
			}
			else {
				isHitPlayer[i] = 0;
			}


			if (CheakCollision(
				wallCollisions[i], coreCollision,
				wall_->GetScale(), core_->GetTransform()->scale)) {
				isHitCore[i] = 1;
			}
			else {
				isHitCore[i] = 0;
			}
		}

		if (CheakCollision(
			wallCollisions[0], playerCollision,
			wall_->GetScale(), player_->GetScale())) {
			isHitPlayer[0] = 1;
		}
		else {
			isHitPlayer[0] = 0;
		}


		/*�X�e�[�W�֘A*/
		//���̉�]
		if (player_->GetPosition().x > stageObject->scale.x) {
			stageObject->rotation = { 0.0f, 0.0f, radian };
			isRotateZ = 1;
		}
		else if (player_->GetPosition().x < -stageObject->scale.x) {
			stageObject->rotation = { 0.0f, 0.0f, -radian };
			isRotateZ = 1;
		}
		else if (player_->GetPosition().z > stageObject->scale.z) {
			stageObject->rotation = { -radian, 0.0f, 0.0f };
			isRotateX = 1;
		}
		else if (player_->GetPosition().z < -stageObject->scale.z) {
			stageObject->rotation = { radian, 0.0f, 0.0f };
			isRotateX = 1;
		}

		//��]��
		if (isRotateX || isRotateZ) {
			core_->SetIsFall(1);
			if (isRotateZ) {
				stageObject->CreateMatRotZ(stageObject->rotation);
				//core_->SetWorldTransform(worldTransform_);
			}
			else if (isRotateX) {
				stageObject->CreateMatRotX(stageObject->rotation);
				//core_->SetWorldTransform(worldTransform_);
			}

			//�X�e�[�W��]���A�v���C���[���ꏏ�ɉ�]����
			player_->Rotate(stageObject);
			wall_->Rotate(stageObject);
			core_->Rotate(stageObject);
			goal_->Rotate(stageObject);
			//wall_->Rotate(worldTransform_);
			rotateTimer += radian;

			if (rotateTimer >= 90.0f) {
				isRotateZ = 0;
				isRotateX = 0;
				rotateTimer = 0;
			}
		}
		//��]��
		else {
			player_->Update(input, wall_->GetTransform(), isHitPlayer);
			core_->Update(stageObject, isHitCore);
			//core_->Update(worldTransform_,wall_->GetWorldTransform(), isHitCore);
		}

		////���������0�ɖ߂�
		//if (worldTransform_.rotation_.x >= PI * 2 || worldTransform_.rotation_.x <= -PI * 2) {
		//	worldTransform_.rotation_.x = 0.0f;
		//}

		//if (worldTransform_.rotation_.z >= PI * 2 || worldTransform_.rotation_.z <= -PI * 2) {
		//	worldTransform_.rotation_.z = 0.0f;
		//}

		//worldTransform_.TransferMatrix();
#pragma endregion
		if (input->PushKey(DIK_R)) { //�N���A�������ł���܂Ŏg�p
			scene = 2;
		}
		break;
	case 2:// �N���A
		if (input->PushKey(DIK_SPACE)) {
			scene = 0;
		}
		break;
	}
	
}

void GameScene::Draw() {
	//�`��O����
	dxCommon->PreDraw();

	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());
	switch (scene)
	{
	case 0:// �^�C�g��
		break;
	case 1:// �Q�[���v���C
#pragma region �Q�[���v���C
		//3D�I�u�W�F�N�g�̕`��
		stageObject->Draw();
		//object3d2->Draw();
		player_->Draw();
		core_->Draw();
		wall_->Draw();
		goal_->Draw();
#pragma endregion
		break;
	case 2:// �N���A
		break;
	}
	
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

	//sprite->Draw(spriteCommon);
	//sprite1->Draw(spriteCommon);
	////�`��R�}���h�����܂�

	//�X�v���C�g�`��㏈��
	spriteCommon->PostDraw();


	dxCommon->PostDraw();


	//DirectX���t���[������ �����܂�
}

//�����蔻��
bool GameScene::CheakCollision(XMFLOAT3 posA, XMFLOAT3 posB, XMFLOAT3 sclA, XMFLOAT3 sclB) {

	float a = 1.1f;
	sclA = { sclA.x * a,sclA.y * a ,sclA.z * a };
	sclB = { sclB.x * a,sclB.y * a ,sclB.z * a };

	if (posA.x - sclA.x < posB.x + sclB.x && posA.x + sclA.x > posB.x - sclB.x &&
		posA.y - sclA.y < posB.y + sclB.y && posA.y + sclA.y > posB.y - sclB.y &&
		posA.z - sclA.z < posB.z + sclB.z && posA.z + sclA.z > posB.z - sclB.z)
	{
		return true;
	}

	return false;
}
