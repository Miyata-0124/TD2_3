#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include <d3d12.h>
#include <string>
#include <wrl.h>
#include <array>
using namespace DirectX;
using namespace Microsoft::WRL;

#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

class SpriteCommon
{
public:
	void Initialize(DirectXCommon* dxCommon);

	void Update(DirectXCommon* dxCommon);

	//�e�N�X�`���ǂݍ���
	void LoadTexture(uint32_t index, const std::string& fileName);

	//�`��p�e�N�X�`���R�}���h�̔��s
	void SetTextureCommands(uint32_t index);

	//�`��O����
	void PreDraw();

	//�`��㏈��
	void PostDraw();

	//�Q�b�^�[
	DirectXCommon* GetDirectXCommon() const { return dxCommon; }
	ComPtr<ID3D12Resource> GetTextureBuffer(uint32_t index) const { return textureBuffers_[index].Get(); }

private:
	HRESULT result;
	DirectXCommon* dxCommon = nullptr;

	ComPtr<ID3DBlob> vsBlob;//���_�V�F�[�_�I�u�W�F�N�g
							   /*���_�V�F�[�_�E�E�E���_���W��ϊ�����̂�����
							   ���f���f�[�^�i�p�ӂ������_�f�[�^�j�̈�_���ɑ΂��āA���_�f�[�^�̃v���O�����������s�����*/
	ComPtr<ID3DBlob> psBlob;//�s�N�Z���V�F�[�_�I�u�W�F�N�g
							   /*�s�N�Z���V�F�[�_�E�E�E�`��F�̐ݒ肪����
							   ���X�^���C�U������������̂P�s�N�Z�����ɑ΂��āA�s�N�Z���V�F�[�_�̃v���O�����������s�����*/
	ComPtr<ID3DBlob> errorBlob;//�G���[�I�u�W�F�N�g

	//�O���t�B�b�N�X�p�C�v���C���ݒ�
	/*�O���t�B�b�N�X�p�C�v���C���E�E�EDirectX�Ɍ��炸�ACG�`��̈�ʓI�Ȏ�@
	�|���S����`�悷��Ƃ��̗���*/
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	//���[�g�V�O�l�`��
	/*���[�g�p�����[�^�̐ݒ���I�u�W�F�N�g����������*/
	ComPtr<ID3D12RootSignature> rootSignature;
	//���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	//���[�g�V�O�l�`���̃V���A���C�Y
	ComPtr<ID3DBlob> rootSigBlob;
	//�p�C�v���C���X�e�[�g�̐���
	ComPtr<ID3D12PipelineState> pipelineState;

	//SRV�̍ő��
	static const size_t kMaxSRVCount = 2056;
	//�e�N�X�`���o�b�t�@
	/*�o�b�t�@�E�E�E�����̎�̂��f�[�^�𑗎�M����ۂɁA�������x��]�����x�̍��A�^�C�~���O�̃Y���Ȃǂ�₤���߂Ƀf�[�^���ꎞ�I�ɒ~���Ă����L�����u��L���̈�̂���*/
	std::array<ComPtr<ID3D12Resource>, kMaxSRVCount> textureBuffers_;

	//�ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	ComPtr<ID3D12DescriptorHeap> srvHeap;

	//�f�t�H���g�e�N�X�`���i�[�f�B���N�g��
	static std::string kDefaultTextureDirectoryPath;

};