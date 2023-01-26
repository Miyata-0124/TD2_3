#pragma once
#include "SpriteCommon.h"

class Sprite
{
public:
	//�萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
	/*�萔�o�b�t�@�E�E�ECPU�œ����v���O�����̕ϐ��Q���AGPU�œ����v���O���}�u���V�F�[�_�[�ɒ萔�Q�i�o�b�t�@�j�Ƃ��đ��荞�ދ@�\*/
	struct ConstBufferDataMaterial {
		XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f }; //�F(RGBA)
	};

	//�萔�o�b�t�@�p�f�[�^�\����(3D�ϊ��s��)
	struct ConstBufferDataTransform {
		XMMATRIX mat;	//3D�ϊ��s��
	};

	struct Vertex {
		XMFLOAT3 pos;	//xyz���W
		XMFLOAT2 uv;	//uv���W
	};

	void Initialize(SpriteCommon* spriteCommon);

	void Update(SpriteCommon* spriteCommon);

	void Draw(SpriteCommon* spriteCommon);

	//�Z�b�^�[
	void SetPosition(const XMFLOAT2& position) { position_ = position; }
	void SetSize(const XMFLOAT2& size) { size_ = size; }
	void SetRotation(const float& rotation) { rotation_.z = rotation; }
	void SetColor(const XMFLOAT4& color) { color_ = color; }
	void SetIndex(const uint32_t textureIndex) { textureIndex_ = textureIndex; }
	//void SetTextureSize(const XMFLOAT2 textureSize) { textureSize_ = textureSize; }
	//�Q�b�^�[
	const XMFLOAT2& GetPosition() const { return position_; }
	const XMFLOAT2& GetSize() const { return size_; }
	const float& GetRotation() const { return rotation_.z; }
	const XMFLOAT4& GetColor() const { return color_; }
	const uint32_t GetTextureIndex() const { return textureIndex_; }
	//const XMFLOAT2 GetTextureSize() const { return textureSize_; }

private:
	//���_�ԍ�
	enum VertexNumber {
		LB,//����
		LT,//����
		RB,//�E��
		RT,//�E��
	};

	HRESULT result;

	//�X�P�[�����O�{��
	XMFLOAT3 scale;
	//��]�p
	XMFLOAT3 rotation_;
	//���W
	XMFLOAT2 position_;
	//�F
	XMFLOAT4 color_ = { 1, 1, 1, 1 };
	//�\���T�C�Y
	XMFLOAT2 size_ = { 100.0f, 100.0f };

	//���_�f�[�^
	Vertex vertices[4] = {
		{{-0.0f,100.0f,0.0f},{0.0f,1.0f}},//����
		{{-0.0f,+0.0f,0.0f},{0.0f,0.0f}},//����
		{{100.0f,100.0f,0.0f},{1.0f,1.0f}},//�E��
		{{100.0f,-0.0f,0.0f},{1.0f,0.0f}},//�E��
	};

	//�e�N�X�`��������W
	//XMFLOAT2 textureLeftTop_ = { 0.0f,0.0f };
	//�e�N�X�`���؂�o���T�C�Y
	//XMFLOAT2 textureSize_ = { 100.0f,100.0f };

	//���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * _countof(vertices));

	//���_�o�b�t�@�̐ݒ�
	/*���_�o�b�t�@�E�E�E���_�f�[�^�p�̃o�b�t�@*/
	D3D12_HEAP_PROPERTIES heapProp{};//�q�[�v�ݒ�

	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};

	ComPtr<ID3D12Resource> vertBuff;

	Vertex* vertMap = nullptr;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	//�萔�o�b�t�@�̐���
	/*�萔�o�b�t�@�E�E�E�S�s�N�Z�����ʂ̃f�[�^�𑗂�Ƃ��ɗ��p����o�b�t�@*/
	ComPtr<ID3D12Resource> constBuffMaterial;

	//�萔�o�b�t�@(�s��p)
	ComPtr<ID3D12Resource> constBuffTransform;

	//�萔�o�b�t�@�}�b�v(�s��p)
	ConstBufferDataTransform* constMapTransform = nullptr;

	ConstBufferDataMaterial* constMapMaterial = nullptr;

	//�e�N�X�`���ԍ�
	uint32_t textureIndex_ = 0;

	SpriteCommon* spriteCommon_;

private:
	//�e�N�X�`���T�C�Y���C���[�W�ɍ��킹��
	void AdjustTextrueSize();
};