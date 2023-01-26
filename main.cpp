//#include "Input.h"
//#include "WinApp.h"
//#include "DirectXCommon.h"
//#include "SpriteCommon.h"
//#include "Sprite.h"
//#include "Object3d.h"
#include "GameScene.h"

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
/*Windows�E�E�E�}�C�N���\�t�g�iMicrosoft�j�Ђ��J���E�̔����Ă���A�R���s���[�^�̃I�y���[�e�B���O�V�X�e���iOS�j���i�̃V���[�Y��*/
/*�G���g���[�|�C���g�E�E�E�v���O�����̎��s�i�K�ɂ����āA�v���O�����⃋�[�`���̎��s����J�n�ʒu�̂���
C����̕W���ł̃G���g���[�|�C���g�́Amain�Ƃ������O�̊֐��̐擪�ʒu*/
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	GameScene gameScene;

	gameScene.Initialize();
	//�Q�[�����[�v
	while (true) {

		//Windows�̃��b�Z�[�W����
		if (gameScene.GetWinApp()->ProcessMesseage()) {
			//�Q�[�����[�v�𔲂���
			break;
		}

		gameScene.Update();

		gameScene.Draw();
	
	}

	gameScene.Finalize();

	return 0;
}
