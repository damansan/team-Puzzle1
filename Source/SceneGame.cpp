#include "System/Graphics.h"
#include "SceneGame.h"
#include "Camera.h"

// 初期化
void SceneGame::Initialize()
{
	//ステージ
	stage = new Stage;
	//プレイヤー
	player = new Player;
	//カメラコントローラー
	cameraController = new  CameraController;

	//カメラの初期設定
	Graphics& graphice = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAt(
		DirectX::XMFLOAT3(0, 10, -10), //視点
		DirectX::XMFLOAT3(0, 0, 0),    //注意点
		DirectX::XMFLOAT3(0, 1, 0)     //上方向
	);

	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(45),
		graphice.GetScreenWidth()/graphice.GetScreenHeight(),
		0.1f,
		1000.0f
	);



}

// 終了化
void SceneGame::Finalize()
{
	//ステージ
	if (stage != nullptr)
	{
		delete stage;
		stage = nullptr;
	}
	//プレイヤー
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	//カメラコントローラー
	if (cameraController != nullptr)
	{
		delete cameraController;
		cameraController = nullptr;
	}
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	//ステージ
	stage->Update(elapsedTime);
	//プレイヤー
	player->Update(elapsedTime);

	//カメラコントローラーの更新処理
	DirectX::XMFLOAT3 target = player->GetPosition();
	target.y += 0.5f;
	cameraController->SeTarget(target);
	cameraController->Update(elapsedTime);
}

// 描画処理
void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ShapeRenderer* shapeRenderer = graphics.GetShapeRenderer();
	ModelRenderer* modelRenderer = graphics.GetModelRenderer();

	// 描画準備
	RenderContext rc;
	rc.deviceContext = dc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f };	// ライト方向（下方向）
	rc.renderState = graphics.GetRenderState();

	//カメラパラメータ設定
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();

	//// ビュー行列
	//{
	//	DirectX::XMFLOAT3 eye = { 0, 10, -10 };	// カメラの視点（位置）
	//	DirectX::XMFLOAT3 focus = { 0, 0, 0 };	// カメラの注視点（ターゲット）
	//	DirectX::XMFLOAT3 up = { 0, 1, 0 };		// カメラの上方向

	//	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&eye);
	//	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	//	DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);
	//	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
	//	DirectX::XMStoreFloat4x4(&rc.view, View);
	//}
	//// プロジェクション行列
	//{
	//	float fovY = DirectX::XMConvertToRadians(45);	// 視野角
	//	float aspectRatio = graphics.GetScreenWidth() / graphics.GetScreenHeight();	// 画面縦横比率
	//	float nearZ = 0.1f;	// カメラが映し出すの最近距離
	//	float farZ = 1000.0f;	// カメラが映し出すの最遠距離
	//	DirectX::XMMATRIX Projection = DirectX::XMMatrixPerspectiveFovLH(fovY, aspectRatio, nearZ, farZ);
	//	DirectX::XMStoreFloat4x4(&rc.projection, Projection);
	//}

	// 3Dモデル描画
	{
		//ステージ
		stage->Render(rc, modelRenderer);
		//プレイヤー
		player->Render(rc, modelRenderer);
	}

	// 3Dデバッグ描画
	{

	}

	// 2Dスプライト描画
	{

	}
}

// GUI描画
void SceneGame::DrawGUI()
{
#ifdef _DEBUG//デバッグの時のみ通る
	player->DrawDebugGUI();
#endif 

}
