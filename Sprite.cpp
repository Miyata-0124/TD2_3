#include "Sprite.h"
#include "DirectXTex.h"
#include <string>

void Sprite::Initialize(SpriteCommon* spriteCommon) {

	scale = { 1.0f,1.0f,1.0f };
	rotation_ = { 0.0f,0.0f,0.0f };
	position_ = { 0.0f,0.0f };

	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	//GPU�ւ̓]���p
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC cbResourceDesc{};
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferDataMaterial) + 0xff) & ~0xff;	//256�o�C�A���C�������g
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	result = spriteCommon->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
		&cbHeapProp,//�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc,//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffMaterial));
	assert(SUCCEEDED(result));

	//�萔�o�b�t�@�̃}�b�s���O

	result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial);//�}�b�s���O
	assert(SUCCEEDED(result));

	constMapMaterial->color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	{

		//�q�[�v�ݒ�
		D3D12_HEAP_PROPERTIES cbHeapProp{};
		cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	//GPU�ւ̓]���p
		//���\�[�X�ݒ�
		D3D12_RESOURCE_DESC cbResourceDesc{};
		cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		cbResourceDesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0xff;	//256�o�C�A���C�������g
		cbResourceDesc.Height = 1;
		cbResourceDesc.DepthOrArraySize = 1;
		cbResourceDesc.MipLevels = 1;
		cbResourceDesc.SampleDesc.Count = 1;
		cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		//�萔�o�b�t�@�̐���
		/*�萔�o�b�t�@�E�E�E�S�s�N�Z�����ʂ̃f�[�^�𑗂�Ƃ��ɗ��p����o�b�t�@*/
		//ComPtr<ID3D12Resource> constBuffMaterial;

		result = spriteCommon->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
			&cbHeapProp,//�q�[�v�ݒ�
			D3D12_HEAP_FLAG_NONE,
			&cbResourceDesc,//���\�[�X�ݒ�
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&constBuffTransform));
		assert(SUCCEEDED(result));

		//�萔�o�b�t�@�̃}�b�s���O
		result = constBuffTransform->Map(0, nullptr, (void**)&constMapTransform);//�}�b�s���O
		assert(SUCCEEDED(result));

	}

	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p

	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;//���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//���_�o�b�t�@�̐���
	result = spriteCommon->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
		&heapProp,//�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc,//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));
	assert(SUCCEEDED(result));

	//GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	/*���z�������E�E�E�n�[�h�f�B�X�N�̈ꕔ���������Ƃ��ė��p����ۂɁA�n�[�h�f�B�X�N��ɍ쐬�����t�@�C��*/
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	//�S���_�ɑ΂���
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];	//���W���R�s�[
	}

	//�q���������
	vertBuff->Unmap(0, nullptr);

	//���_�o�b�t�@�r���[�̐���
	/*GPU�ɒ��_�o�b�t�@�̏ꏊ�������邽�߂̂���*/
	//GPU���z�A�h���X
	/*���z�A�h���X�E�E�E�R���s���[�^���̃������̈�ɑ΂��āA���������u���ł̕����I�Ȕz�u�Ƃ͓Ɨ��Ɋ��蓖�Ă�ꂽ���ݏ��i�A�h���X�j�̂���*/
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//���_�o�b�t�@�̃T�C�Y
	vbView.SizeInBytes = sizeVB;
	//���_����̃f�[�^�T�C�Y
	vbView.StrideInBytes = sizeof(vertices[0]);

	//�e�N�X�`���T�C�Y���C���[�W�ɍ��킹��
	//if (textureIndex != UINT32_MAX) {
	//	textureIndex_ = textureIndex;
	//	AdjustTextrueSize();
	//	//�e�N�X�`���T�C�Y���X�v���C�g�̃T�C�Y�ɓK�p
	//	size_ = textureSize_;
	//}
}

void Sprite::Update(SpriteCommon* spriteCommon) {

}

void Sprite::Draw(SpriteCommon* spriteCommon) {
	//�e�N�X�`���R�}���h
	spriteCommon->SetTextureCommands(textureIndex_);

	//���_�f�[�^
	vertices[LB].pos = { 0.0f,		size_.y,	0.0f };
	vertices[LT].pos = { 0.0f,		0.0f,		0.0f };
	vertices[RB].pos = { size_.x,	size_.y,	0.0f };
	vertices[RT].pos = { size_.x,	0.0f,		0.0f };

	ComPtr<ID3D12Resource> textureBuffer = spriteCommon->GetTextureBuffer(textureIndex_);
	//�w��ԍ��̉摜���ǂݍ��ݍς݂Ȃ�
	//if (textureBuffer) {
	//	//�e�N�X�`�����擾
	//	D3D12_RESOURCE_DESC resDesc = textureBuffer->GetDesc();

	//	float tex_left = textureLeftTop_.x / resDesc.Width;
	//	float tex_right = (textureLeftTop_.x + textureSize_.x) / resDesc.Width;
	//	float tex_top = textureLeftTop_.y / resDesc.Height;
	//	float tex_bottom = (textureLeftTop_.y + textureSize_.y) / resDesc.Height;
	//	//���_��UV�ɔ��f����
	//	vertices[LB].uv = { tex_left, tex_bottom };		//����
	//	vertices[LT].uv = { tex_left, tex_top };		//����
	//	vertices[RB].uv = { tex_right, tex_bottom };	//�E��
	//	vertices[RT].uv = { tex_right, tex_top };		//�E��
	//}

	//���_�f�[�^��GPU�ɓ]��
	std::copy(std::begin(vertices), std::end(vertices), vertMap);

	//�F����GPU�ɓ]��
	constMapMaterial->color = color_;

	//�P�ʍs�����
	constMapTransform->mat = XMMatrixIdentity();
	//���[���h�ϊ��s��
	XMMATRIX matWorld;
	matWorld = XMMatrixIdentity();

	XMMATRIX matRot;
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation_.z));
	matWorld *= matRot;

	XMMATRIX matTrans;
	matTrans = XMMatrixTranslation(position_.x, position_.y, 0.0f);
	matWorld *= matTrans;

	//�ˉe�ϊ��s��
	XMMATRIX matProjection = XMMatrixIdentity();
	matProjection.r[3].m128_f32[0] = -1.0f;
	matProjection.r[3].m128_f32[1] = 1.0f;
	matProjection.r[0].m128_f32[0] = 2.0f / WinApp::window_width;
	matProjection.r[1].m128_f32[1] = -2.0f / WinApp::window_height;
	constMapTransform->mat = matWorld * matProjection;

	//���_�o�b�t�@�r���[�̐ݒ�R�}���h
	spriteCommon->GetDirectXCommon()->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);

	spriteCommon->GetDirectXCommon()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	spriteCommon->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());

	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	spriteCommon->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(2, constBuffTransform->GetGPUVirtualAddress());

	//�`��R�}���h
	spriteCommon->GetDirectXCommon()->GetCommandList()->DrawInstanced(_countof(vertices), 1, 0, 0);

}

void Sprite::AdjustTextrueSize() {
	ComPtr<ID3D12Resource> textureBuffer = spriteCommon_->GetTextureBuffer(textureIndex_);
	assert(textureBuffer);

	//�e�N�X�`�����擾
	D3D12_RESOURCE_DESC resDesc = textureBuffer->GetDesc();

	//textureSize_.x = static_cast<float>(resDesc.Width);
	//textureSize_.y = static_cast<float>(resDesc.Height);
}