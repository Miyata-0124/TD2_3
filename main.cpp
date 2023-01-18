#include "Audio.h"
#include "DX12base.h"
#include "GameScene.h"
#include "Texture.h"
#include "WinApp.h"
//#include "AxisIndicator.h"
//include "PrimitiveDrawer.h"

//WinApp winApp_;
using namespace DirectX;
using namespace Microsoft::WRL;

#pragma region//�֐��̃v���g�^�C�v�錾
//�E�B���h�E�v���V�[�V��
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

#pragma endregion//�֐��̃v���g�^�C�v�錾

//main�֐�
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	WinApp* win = nullptr;
	win->Initialize();
	DX12base* dxCommon = nullptr;
	// �ėp�@�\
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText* debugText = nullptr;
	//AxisIndicator* axisIndicator = nullptr;
	//PrimitiveDrawer* primitiveDrawer = nullptr;
	GameScene* gameScene = nullptr;

	// �Q�[���E�B���h�E�̍쐬
	//n = WinApp::GetInstance();
	//n->CreateGameWindow();

	// DirectX����������
	*dxCommon = DX12base::GetInstance();
	dxCommon->Initialize();

#pragma region �ėp�@�\������
	// ���͂̏�����
	*input = Input::GetInstance();
	//input->Initialize();

	// �I�[�f�B�I�̏�����
	//audio = Audio::GetInstance();
	//audio->Initialize();

	// �e�N�X�`���}�l�[�W���̏�����
	//Texture::GetInstance()->Initialize(dxCommon->GetDevice());
	//Texture::Load("white1x1.png");

	// �X�v���C�g�ÓI������
	//Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// �f�o�b�O�e�L�X�g������
	debugText = DebugText::GetInstance();
	debugText->Initialize();

	// 3D���f���ÓI������
	//Model::StaticInitialize();

	// �������\��������
	//axisIndicator = AxisIndicator::GetInstance();
	//axisIndicator->Initialize();

	//primitiveDrawer = PrimitiveDrawer::GetInstance();
	//primitiveDrawer->Initialize();

#pragma endregion

	// �Q�[���V�[���̏�����
	gameScene = new GameScene();
	gameScene->Initialize(win);

#pragma region//�Q�[�����[�v
	while (true) {
		// ���b�Z�[�W����
		if (win->ProcessMesseage()) {
			break;
		}

		// ���͊֘A�̖��t���[������
		input->Update();
		// �Q�[���V�[���̖��t���[������
		gameScene->Update();
		// ���\���̍X�V
		//axisIndicator->Update();

		// �`��J�n
		dxCommon->PreDraw();
		// �Q�[���V�[���̕`��
		gameScene->Draw();
		// ���\���̕`��
		//axisIndicator->Draw();
		// �v���~�e�B�u�`��̃��Z�b�g
		//primitiveDrawer->Reset();
		// �`��I��
		dxCommon->PostDraw();
	}

	// �e����
	//SafeDelete(gameScene);
	delete gameScene;
	//audio->Finalize();

	// �Q�[���E�B���h�E�̔j��
	//win->TerminateGameWindow();
	win->Finalize();
	return 0;
}