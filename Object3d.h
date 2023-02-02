﻿#pragma once
#include "Model.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "MathFunc.h"
//#include "WorldTransform.h"
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
//#include <DirectXMath.h>
//#include <math.h>
#include <d3dx12.h>
#include <string>

/// <summary>
/// 3Dオブジェクト
/// </summary>
class Object3d
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス

	// 定数バッファ用データ構造体B0
	struct ConstBufferDataB0
	{
		XMMATRIX mat;	// ３Ｄ変換行列
	};

private: // 定数
	static const int division = 50;			// 分割数
	static const float radius;				// 底面の半径
	static const float prizmHeight;			// 柱の高さ
	static const int planeCount = division * 2 + division * 2;		// 面の数
	static const int vertexCount = 4;		// 頂点数
	static const int indexCount = 3 * 2;		// インデックス数

public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	static void StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">描画コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Object3d* Create();

	/// <summary>
	/// 視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	static const XMFLOAT3& GetEye() { return eye; }

	/// <summary>
	/// 視点座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	static void SetEye(XMFLOAT3 eye);

	/// <summary>
	/// 注視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	static const XMFLOAT3& GetTarget() { return target; }

	/// <summary>
	/// 注視点座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	static void SetTarget(XMFLOAT3 target);

	/// <summary>
	/// ベクトルによる移動
	/// </summary>
	/// <param name="move">移動量</param>
	static void CameraMoveVector(XMFLOAT3 move);

	/// <summary>
	/// ベクトルによる視点移動
	/// </summary>
	static void CameraMoveEyeVector(XMFLOAT3 move);


private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;
	// デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// デスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// 頂点バッファ
	static ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	static ComPtr<ID3D12Resource> indexBuff;
	// テクスチャバッファ
	static ComPtr<ID3D12Resource> texbuff;
	// シェーダリソースビューのハンドル(CPU)
	static CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	static CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// ビュー行列
	static XMMATRIX matView;
	// 射影行列
	static XMMATRIX matProjection;
	// 視点座標
	static XMFLOAT3 eye;
	// 注視点座標
	static XMFLOAT3 target;
	// 上方向ベクトル
	static XMFLOAT3 up;
	// 頂点バッファビュー
	static D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	static D3D12_INDEX_BUFFER_VIEW ibView;
	// 頂点データ配列
	//static VertexPosNormalUv vertices[vertexCount];
	static std::vector<Model::VertexPosNormalUv> vertices;
	// 頂点インデックス配列
	static std::vector<unsigned short> indices;
	//マテリアル
	//static Material material;

private:// 静的メンバ関数
	/// <summary>
	/// デスクリプタヒープの初期化
	/// </summary>
	//static void InitializeDescriptorHeap();

	/// <summary>
	/// カメラ初期化
	/// </summary>
	/// <param name="window_width">画面横幅</param>
	/// <param name="window_height">画面縦幅</param>
	static void InitializeCamera(int window_width, int window_height);

	/// <summary>
	/// グラフィックパイプライン生成
	/// </summary>
	/// <returns>成否</returns>
	static void InitializeGraphicsPipeline();

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	//static void LoadTexture(const std::string& directoryPath,const std::string& filename);

	/// <summary>
	/// モデル作成
	/// </summary>
	static void CreateModel();

	/// <summary>
	/// ビュー行列を更新
	/// </summary>
	static void UpdateViewMatrix();

	/// <summary>
	/// マテリアルの読み込み
	/// </summary>
	//static void LoadMaterial(const std::string& directoryPath, const std::string& filename);

public: // メンバ関数
	bool Initialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void CreateMatIdentity(XMMATRIX& matrix)
	{
		matrix = {
		   1.0f,0,0,0,
		   0,1.0f,0,0,
		   0,0,1.0f,0,
		   0,0,0,1.0f,
		};
	}

	void CreateMatRotX(XMFLOAT3& rot) {
		XMMATRIX matrotX;
		matrotX = XMMatrixIdentity();
		matrotX *= XMMatrixRotationX(XMConvertToRadians(rot.x));

		matWorld *= matrotX;

		TransferMatrix();
	}


	void CreateMatRotY(XMFLOAT3& rot) {
		XMMATRIX matrotY;
		matrotY = XMMatrixIdentity();
		matrotY *= XMMatrixRotationX(XMConvertToRadians(rot.y));
    
		matWorld *= matrotY;

		TransferMatrix();
	}
	//void CreateMatRotY(Matrix4& matrix, Vector3 rot) {
	//	Matrix4 matrotY;
	//	//CreateMatIdentity(matrotY);
	//	matrotY.m[1][1] = cos(rot.y);
	//	matrotY.m[1][2] = sin(rot.y);
	//	matrotY.m[2][1] = -sin(rot.y);
	//	matrotY.m[2][2] = cos(rot.y);

	//	matrix *= matrotY;
	//}
	void CreateMatRotZ(XMFLOAT3& rot) {

		XMMATRIX matrotZ;
		matrotZ = XMMatrixIdentity();
		matrotZ *= XMMatrixRotationZ(XMConvertToRadians(rot.z));

		matWorld *= matrotZ;

		TransferMatrix();
	}

	XMMATRIX& GetMatrix() { return matWorld; }

	void TransferMatrix();

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const XMFLOAT3& GetPosition() const { return position; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(const XMFLOAT3& position) { this->position = position; }
	void SetScale(const XMFLOAT3& scale) { this->scale = scale; }
	void SetRotation(const XMFLOAT3& rotation) { this->rotation = rotation; }

	void CreateMatTrans(const XMFLOAT3& trans)
	{
		XMMATRIX  matTrams;
		matTrans = XMMatrixIdentity();
		matTrans *= XMMatrixTranslation(trans.x, trans.y, trans.z);

		matWorld *= matTrans;
		TransferMatrix();
	}

	//setter
	void SetModel(Model* model) { this->model = model; }

private: // メンバ変数
	//モデル
	Model* model = nullptr;

	ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ
	//ComPtr<ID3D12Resource> constBuffB1; // 定数バッファ

public:
	//WorldTransform worldTransform;
	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 1.0f,1.0f,1.0f };
	// ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	// 親オブジェクト
	Object3d* parent = nullptr;

	XMMATRIX matScale, matRot, matTrans;
};