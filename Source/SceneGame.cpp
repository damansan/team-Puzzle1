#include "System/Graphics.h"
#include "SceneGame.h"
#include "Camera.h"
#include "CameraController.h"
#include "StageManager.h"
#include "BoxManager.h"
#include "TrueBox.h"
#include "FalseBox.h"

// 初期化
void SceneGame::Initialize()
{
	//ステージ初期化
	StageManager& stageManager = StageManager::Instance();
	//ステージ配置
	StageManager::Generate();
	//プレイヤー
	player = new Player;
	//カメラコントローラー
	cameraController = new CameraController;
	//ボックス初期化
	BoxManager& boxManager = BoxManager::Instance();
	//ボックス配置
	BoxManager::Generate();

	//カメラ初期設定
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAt(
		DirectX::XMFLOAT3(0, 10, -10), //始点
		DirectX::XMFLOAT3(0, 0, 0),    //注視点
		DirectX::XMFLOAT3(0, 1, 0)     //上方向
	);
	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(45),//視野角
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),//画面アスペクト比
		0.1f,    //クリップ距離(近)
		1000.0f  //クリップ距離(遠)
	);

	//ジャッジ
	judge = new Judge;

}

// 終了化
void SceneGame::Finalize()
{
	//ステージ
	StageManager::Instance().Clear();
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
	//Trueボックス全削除
	BoxManager::Instance().Clear();
	//ジャッジ
	if (judge != nullptr)
	{
		delete judge;
		judge = nullptr;
	}
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{

	//ステージ更新
	StageManager::Instance().Update(elapsedTime);
	//プレイヤー更新
	player->Update(elapsedTime);
	//Trueボックス更新
	BoxManager::Instance().Update(elapsedTime);
	
	//カメラコントローラー(プレイヤーの腰あたりをターゲット)
	DirectX::XMFLOAT3 target = player->GetPosition();
	target.y += 0.5f;
	cameraController->SetTarget(target);
	cameraController->Update(elapsedTime);
	
	//ジャッジ更新
	judge->GetPosition();
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


	//カメラパラメーター設定
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();


	// 3Dモデル描画
	{
		//ステージ
		StageManager::Instance().Render(rc, modelRenderer);
		//プレイヤー
		player->Render(rc, modelRenderer);
		//Trueボックス
		BoxManager::Instance().Render(rc, modelRenderer);
	}

	// 3Dデバッグ描画
	{
#ifdef _DEBUG
		//プレイヤー
		player->RenderDebugPrimiteve(rc, shapeRenderer);
		//Trueボックス
		BoxManager::Instance().RenderDebugPrimiteve(rc, shapeRenderer);

#endif

	}

	// 2Dスプライト描画
	{

	}
}

// GUI描画
void SceneGame::DrawGUI()
{
#ifdef _DEBUG
	//プレイヤーデバッグ
	player->DrawGUI();
	//カメラコントローラー
	cameraController->DrawGUI();
	judge->DrawGUI();

#endif 
}

