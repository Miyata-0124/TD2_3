#include "DirectXCommon.h"
#include <cassert>
#include <thread>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

using namespace Microsoft::WRL;

void DirectXCommon::Initialize(WinApp* winApp)
{
	//FPS�Œ菉����
	InitializeFixFPS();

	//NULL���o
	assert(winApp);

	//�����o�ϐ��ɋL�^
	this->winApp = winApp;

	//�f�o�C�X�̐���
	InitializeDevice();
	//�R�}���h�֘A�̏�����
	InitializeCommand();
	//�X���b�v�`�F�[���̏�����
	InitializeSwapchain();
	//�����_�[�^�[�Q�b�g�r���[�̏�����
	InitializeRenderTargetView();
	//�[�x�o�b�t�@�̏�����
	InitializeDepthBuffer();
	//�t�F���X�̏�����
	InitializeFence();
}

void DirectXCommon::InitializeDevice()
{
#ifdef _DEBUG
	//�f�o�b�O���C���[���I����
	/*�f�o�b�O���C���[�E�E�E�f�o�b�O���邽�߂̑w*/
	ComPtr<ID3D12Debug1> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}
#endif

	//DXGI�t�@�N�g���[�̐���
	/*DXGI�t�@�N�g���[�E�E�EDXGI�̊e��I�u�W�F�N�g�𐶐�����N���X*/
	/*DXGI�E�E�EDirectX �O���t�B�b�N�X �C���t���X�g���N�`���[(��ՂƂȂ�ݔ���v�f�̂���)�̗�
	�A�_�v�^�[�̗񋓂�X���b�v�`�F�C���̍쐬�������Ă����*/
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(result));

	//�A�_�v�^�[�̗񋓗p
	/*�A�_�v�^�[�E�E�E���󂷂�΁u�K����������́v
	�u�𗬂��璼���ւ̓d���̕ϊ��v�Ɓu�d���̕ϊ��v����Ȗ���
	�����ł̓O���t�B�b�N�{�[�h�̃A�_�v�^�̂��Ƃ��w��*/
	std::vector<ComPtr<IDXGIAdapter4>> adapters;
	//�����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	ComPtr<IDXGIAdapter4> tmpAdapter;

	//�p�t�H�[�}���X���������̂��珇�ɁA���ׂẴA�_�v�^�[��񋓂���
	for (UINT i = 0;
		dxgiFactory->EnumAdapterByGpuPreference(i,
			DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
			IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND;
		i++) {
		//���I�z��ɒǉ�����
		adapters.push_back(tmpAdapter);
	}

	//�Ó��ȃA�_�v�^��I�ʂ���
	for (size_t i = 0; i < adapters.size(); i++) {
		DXGI_ADAPTER_DESC3 adapterDesc;
		//�A�_�v�^�[�̏����擾����
		adapters[i]->GetDesc3(&adapterDesc);

		//�\�t�g�E�F�A�f�o�C�X�����
		/*�\�t�g�E�F�A�f�o�C�X�E�E�E�\�t�g�E�F�A�ŃG�~�����[�V�������Ă�����̂�I���{�[�h�O���t�B�b�N*/
		/*�G�~�����[�V�����E�E�E���鑕�u��\�t�g�E�F�A�A�V�X�e���̋�����ʂ̃\�t�g�E�F�A�Ȃǂɂ���Ė͕킵�A��ւƂ��ē��삳���邱��*/
		/*�I���{�[�h�O���t�B�b�N�E�E�E�p�[�\�i���R���s���[�^�̃}�U�[�{�[�h��ɓ��ڂ���Ă���O���t�B�b�N�X�R���g���[�� (GPU) �̂���*/
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			//�f�o�C�X���̗p���ă��[�v�𔲂���
			/*�f�o�C�X�E�E�E�p�\�R���E�^�u���b�g�E�X�}�[�g�t�H����A�����Ɛڑ����Ďg�����u�̑���*/
			tmpAdapter = adapters[i];
			break;
		}
	}

	//�Ή����x���̔z��
	/*�Ή����x��(�@�\���x��)�E�E�E���m�ɒ�`���ꂽGPU�@�\�̃Z�b�g*/
	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL featureLevel;

	for (size_t i = 0; i < _countof(levels); i++) {
		//�̗p�����A�_�v�^�[�Ńf�o�C�X�𐶐�
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i],
			IID_PPV_ARGS(&device));
		if (result == S_OK) {
			//�f�o�C�X�𐶐��ł������_�Ń��[�v�𔲂���
			featureLevel = levels[i];
			break;
		}
	}

#ifdef _DEBUG
	ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue)))) {
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);

		D3D12_MESSAGE_ID denyIds[] = {
			D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
		};

		D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
		D3D12_INFO_QUEUE_FILTER filter{};
		filter.DenyList.NumIDs = _countof(denyIds);
		filter.DenyList.pIDList = denyIds;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;

		infoQueue->PushStorageFilter(&filter);

	}
#endif // _DEBUG

}

void DirectXCommon::InitializeCommand()
{
	//�R�}���h�A���P�[�^�𐶐�
/*�R�}���h�A���P�[�^�E�E�E�R�}���h���X�g�ɐςݍ��ރo�b�t�@���m�ۂ���I�u�W�F�N�g*/
	result = device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&commandAllocator)
	);
	assert(SUCCEEDED(result));

	//�R�}���h���X�g�𐶐�
	/*�R�}���h���X�g�E�E�E��A�̗���̕`�施�߂��R�}���h�Ƃ��Đςݍ��܂ꂽ�o�b�t�@���X�g*/
	result = device->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		commandAllocator.Get(),
		nullptr,
		IID_PPV_ARGS(&commandList)
	);
	assert(SUCCEEDED(result));

	//�R�}���h�L���[�̐ݒ�
	/*�R�}���h�L���[�E�E�E�R�}���h�̑҂��s��*/
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	//�R�}���h�L���[�𐶐�
	result = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	assert(SUCCEEDED(result));
}

void DirectXCommon::InitializeSwapchain()
{
	//�X���b�v�`�F�[���̐ݒ�
	/*�X���b�v�`�F�[���E�E�E�_�u���o�b�t�@�����O���ȒP�Ɏ�������ׂ�DirecctX���p�ӂ����d�g��*/
	/*�_�u���o�b�t�@�����O�E�E�E��ʂ�摜��A���I�ɏ���������ۂɁA�`��̈�Ɠ����T�C�Y�̃o�b�t�@�̈�����������2�p�ӂ��āA���݂ɕ`�揈�����s�Ȃ���@*/
	swapChainDesc.Width = 1280;
	swapChainDesc.Height = 720;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//�F���̏���
	swapChainDesc.SampleDesc.Count = 1;//�}���`�T���v�����Ȃ�
									   /*�}���`�T���v���E�E�E��ԃA���`�G�C���A�V���O�̈��ł���A�R���s���[�^�O���t�B�b�N�X�ŃW���M�[���������邽�߂Ɏg�p������@*/
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;//�o�b�N�o�b�t�@�p
													   /*�o�b�N�o�b�t�@�E�E�E��ʂɕ`�悵�Ă��Ȃ����̕`��L�����o�X*/
	swapChainDesc.BufferCount = 2;//�o�b�t�@�����Q�ɐݒ�
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//�t���b�v��͔j��
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//IDXGISwapChain1��ComPtr��p��
	ComPtr<IDXGISwapChain1> swapChain1;

	//�X���b�v�`���[���̐���
	result = dxgiFactory->CreateSwapChainForHwnd(
		commandQueue.Get(),
		winApp->GetHwnd(),
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapChain1);
	assert(SUCCEEDED(result));

	//��������IDXGISwapChain1�̃I�u�W�F�N�g��IDXGISwapChain4�ɕϊ�����
	swapChain1.As(&swapChain);
}

void DirectXCommon::InitializeRenderTargetView()
{
	//RTV�p�f�X�N���v�^�q�[�v�̐ݒ�
	/*�f�X�N���v�^�q�[�v�E�E�EGPU��ɍ����f�X�N���v�^��ۑ����邽�߂̔z��*/
	/*�f�X�N���v�^�E�E�EGPU��������ɑ��݂���A�l�X�ȃf�[�^��o�b�t�@�̎�ނ�ʒu�A�傫���������\���̂̂悤�Ȃ���*/
	
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//�����_�[�^�[�Q�b�g�r���[
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount;//���\�̂Q��

	backBuffers.resize(swapChainDesc.BufferCount);

	//RTV�p�f�X�N���v�^�q�[�v�̐���
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));

	//�X���b�v�`�F�[���̑S�Ẵo�b�t�@�ɂ��ď�������
	for (size_t i = 0; i < backBuffers.size(); i++) {
		//�X���b�v�`�F�[������o�b�t�@���擾
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		//�f�X�N���v�^�q�[�v�̃n���h�����擾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		//�����\���ŃA�h���X�������
		rtvHandle.ptr += i * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		//�����_�[�^�[�Q�b�g�r���[�̐ݒ�
		/*�����_�[�^�[�Q�b�g�r���[�E�E�E�o�b�N�o�b�t�@��`��L�����o�X�Ƃ��Ĉ����ׂ̃I�u�W�F�N�g*/
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		//�V�F�[�_�[�̌v�Z���ʂ�SRGB�ɕϊ����ď�������
		/*�V�F�[�_�[�E�E�E3�����R���s���[�^�O���t�B�b�N�X�ɂ����āA�V�F�[�f�B���O�i�A�e�����j���s���R���s���[�^�v���O�����̂���
		�ushade�v�Ƃ́u����ɕω�������v�u�A�e�E�O���f�[�V������t����v�Ƃ����Ӗ�
		�ushader�v�͒��_�F��s�N�Z���F�Ȃǂ����X�ɕω���������́i����̓I�ɁA���`�̈Ӗ��Ō����Ί֐��j���Ӗ�����*/
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		//�����_�[�^�[�Q�b�g�r���[�̐���
		device->CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, rtvHandle);
	}
}

void DirectXCommon::InitializeDepthBuffer()
{
	//�[�x�o�b�t�@
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC depthResourceDesc{};
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResourceDesc.Width = WinApp::window_width;		//�����_�[�^�[�Q�b�g�ɍ��킹��
	depthResourceDesc.Height = WinApp::window_height;	//�����_�[�^�[�Q�b�g�ɍ��킹��
	depthResourceDesc.DepthOrArraySize = 1;
	depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;//�[�x�l�t�H�[�}�b�g
	depthResourceDesc.SampleDesc.Count = 1;
	depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;//�f�v�X�X�e���V��

	//�[�x�l�p�q�[�v�v���p�e�B
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	//�[�x�l�̃N���A�ݒ�
	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;//�[�x�l1.0f(�ő�l)�ŃN���A
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;//�[�x�l�t�H�[�}�b�g

	//�[�x�o�b�t�@����
	result = device->CreateCommittedResource(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,//�[�x�l�������݂Ɏg�p
		&depthClearValue,
		IID_PPV_ARGS(&depthBuff)
	);

	//�[�x�o�b�t�@�r���[�p�f�X�N���v�^�q�[�v����
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;//�[�x�r���[��1��

	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;//�f�v�X�X�e���V���r���[
	result = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

	//�[�x�o�b�t�@�r���[����
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;//�[�x�t�H�[�}�b�g
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	device->CreateDepthStencilView(
		depthBuff.Get(),
		&dsvDesc,
		dsvHeap->GetCPUDescriptorHandleForHeapStart()
	);
}

void DirectXCommon::InitializeFence()
{
	//�t�F���X�̐���
	/*�t�F���X�E�E�ECPU��GPU�œ������Ƃ邽�߂�DirecctX�̎d�g��*/
	result = device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
}

void DirectXCommon::PreDraw()
{
	//�o�b�N�o�b�t�@�̔ԍ����擾(2�Ȃ̂�0�Ԃ�1��)
	UINT bbIndex = swapChain->GetCurrentBackBufferIndex();

	// 1 ���\�[�X�o���A�ŏ������݉\�ɕύX
	/*���\�[�X�o���A�E�E�E�o�b�N�o�b�t�@��`��ł����Ԃɐ؂�ւ�����A�`���Ƀo�b�t�@��\���p�̏�Ԃɖ߂��R�}���h*/

	barrierDesc.Transition.pResource = backBuffers[bbIndex].Get();//�o�b�N�o�b�t�@���w��
	//barrierDesc.Transition.Subresource = bbIndex;
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;		//�\����Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;//�`���Ԃ�
	commandList->ResourceBarrier(1, &barrierDesc);

	// 2 �`���̕ύX
	//�����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle =
		rtvHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
	//�[�x�X�e���V���r���[�p�f�X�N���v�^�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
	commandList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	// 3 ��ʃN���A           R      G     B     A
	FLOAT clearColor[] = { 0.0f, 0.25f, 0.5f, 0.0f };

	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	//�r���[�|�[�g�ݒ�R�}���h
	/*�r���[�|�[�g�E�E�E�`��̈�
	���_�V�F�[�_����̏o�͍��W�̓r���[�|�[�g�̗̈�Ƀ}�b�s���O�����*/
	D3D12_VIEWPORT viewport{};
	viewport.Width = WinApp::window_width;	//����
	viewport.Height = WinApp::window_height;//�c��
	viewport.TopLeftX = 0;			//����X
	viewport.TopLeftY = 0;			//����Y
	viewport.MinDepth = 0.0f;		//�ŏ��[�x
	viewport.MaxDepth = 1.0f;		//�ő�[�x
	//�r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	commandList->RSSetViewports(1, &viewport);

	//�V�U�[��`
	/*�`��̈�̍i�荞�ݐݒ�̈��
	���͈̔͂��炸�ꂽ�����̕`����J�b�g����*/
	D3D12_RECT scissorRect{};
	scissorRect.left = 0;									//�؂蔲�����W��
	scissorRect.right = scissorRect.left + WinApp::window_width;	//�؂蔲�����W�E
	scissorRect.top = 0;									//�؂蔲�����W��
	scissorRect.bottom = scissorRect.top + WinApp::window_height;	//�؂蔲�����W��
	//�V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	commandList->RSSetScissorRects(1, &scissorRect);

}

void DirectXCommon::PostDraw()
{
	//�o�b�N�o�b�t�@�̔ԍ����擾
	UINT bbIndex = swapChain->GetCurrentBackBufferIndex();

	// 5 ���\�[�X�o���A��߂�
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;//�`���Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;		//�\����Ԃ�
	commandList->ResourceBarrier(1, &barrierDesc);

	//���߂̃N���[�Y
	result = commandList->Close();
	assert(SUCCEEDED(result));

	//�R�}���h���X�g�̎��s
	ID3D12CommandList* commandLists[] = { commandList.Get() };
	commandQueue->ExecuteCommandLists(1, commandLists);

	//��ʂɕ\������o�b�t�@���t���b�v(���\�̓��ւ�)
	result = swapChain->Present(1, 0);
	assert(SUCCEEDED(result));

	//�R�}���h�̎��s������҂�
	commandQueue->Signal(fence.Get(), ++fenceVal);
	if (fence->GetCompletedValue() != fenceVal) {
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		if (event != 0) {
			fence->SetEventOnCompletion(fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}
	}

	//FPS�Œ�
	UpdateFixFPS();

	//�L���[���N���A
	result = commandAllocator->Reset();
	assert(SUCCEEDED(result));
	//�ĂуR�}���h���X�g�𒙂߂鏀��
	result = commandList->Reset(commandAllocator.Get(), nullptr);
	assert(SUCCEEDED(result));
}

void DirectXCommon::InitializeFixFPS()
{
	//���ݎ��Ԃ��L�^����
	reference_ = std::chrono::steady_clock::now();
}

void DirectXCommon::UpdateFixFPS()
{
	// 1/60�b�҂�����̎���
	const std::chrono::microseconds kMinTime(uint64_t(1000000.0f / 60.0f));
	// 1/60�b���킸���ɒZ������
	const std::chrono::microseconds kMinCheckTime(uint64_t(1000000.0f / 65.0f));

	//���ݎ��Ԃ��擾����
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	//�O��L�^����̌o�ߎ��Ԃ��擾����
	std::chrono::microseconds elapsed =
		std::chrono::duration_cast<std::chrono::microseconds>(now - reference_);

	// 1/60�b(���킸���ɒZ������)�o���ĂȂ��ꍇ
	if (elapsed < kMinCheckTime) {
		// 1/60�b�o�߂���܂Ŕ����ȃX���[�v���J��Ԃ�
		while (std::chrono::steady_clock::now() - reference_ < kMinTime) {
			//1�}�C�N���b�X���[�v
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
	}
	//���݂̎��Ԃ��L�^����
	reference_ = std::chrono::steady_clock::now();
}