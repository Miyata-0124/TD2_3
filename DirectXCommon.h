#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <vector>
#include <chrono>
#include "WinApp.h"

class DirectXCommon
{
public://�����o�֐�
	//������
	void Initialize(WinApp* winApp);
	//�f�o�C�X�̐���
	void InitializeDevice();
	//�R�}���h�֘A�̏�����
	void InitializeCommand();
	//�X���b�v�`�F�[���̏�����
	void InitializeSwapchain();
	//�����_�[�^�[�Q�b�g�r���[�̏�����
	void InitializeRenderTargetView();
	//�[�x�o�b�t�@�̏�����
	void InitializeDepthBuffer();
	//�t�F���X�̏�����
	void InitializeFence();
	//�`��O����
	void PreDraw();
	//�`��㏈��
	void PostDraw();

	//�f�o�C�X�擾
	ID3D12Device* GetDevice() const { return device.Get(); }
	//�R�}���h���X�g�擾
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }

private://�����o�ϐ�
	HRESULT result;
	
	//WindowsAPI
	WinApp* winApp = nullptr;

	//DirectX12�f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	//DXGI�t�@�N�g��
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;

	//�R�}���h�A���P�[�^�[
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	//�R�}���h���X�g
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	//�R�}���h�L���[
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;

	//�X���b�v�`�F�[��
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	//RTV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	//�o�b�N�o�b�t�@
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;

	//�[�x�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;

	//�t�F���X
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;

	//���\�[�X�o���A
	D3D12_RESOURCE_BARRIER barrierDesc{};

private://�����o�֐�

	//FPS�Œ菉����
	void InitializeFixFPS();
	//FPS�Œ�X�V
	void UpdateFixFPS();
	//�L�^����(FPS�Œ�p)
	std::chrono::steady_clock::time_point reference_;
};

