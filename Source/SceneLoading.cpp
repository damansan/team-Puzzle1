#include"System/Graphics.h"
#include"System/input.h"
#include"SceneLoading.h"
#include"SceneManager.h"

//初期化
void SceneLoading::Initialize()
{
	//スプライト初期化
	sprite = new Sprite("Data/Sprite/LoadingIcon.png");
	//スレッド開始
	thread = new std::thread(LoadingThread, this);
}

//終了化
void SceneLoading::Finalize()
{
	//スプライト
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
	//スレッド終了化
	if (thread != nullptr)
	{
		thread->join();
		delete thread;
		thread = nullptr;
	}
}

//更新処理
void SceneLoading::Update(float elapsedTime)
{
	constexpr float speed = 180;
	angle += speed * elapsedTime;

	//次のシーンの準備が完了してたらシーンを切り替える
	if (nextScene->IsReady())
	{
		SceneManager::Instance().ChangeScene(nextScene);
		nextScene = nullptr;
	}
}

//描画処理
void SceneLoading::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	RenderState* renderState = graphics.GetRenderState();

	//描画処理
	RenderContext rc;
	rc.deviceContext = dc;
	rc.renderState = graphics.GetRenderState();

	//2Dスプライト描画
	{
		//右下にロードアイコンを描画
		float screenWidth = static_cast<float>(graphics.GetScreenWidth());
		float screenHeight = static_cast<float>(graphics.GetScreenHeight());
		float spriteWidth = 256;
		float spriteHeight = 256;
		float positionX = screenWidth - spriteWidth;
		float positionY = screenHeight - spriteHeight;

		sprite->Render(rc,
			positionX, positionY, 0, spriteWidth, spriteHeight,
			angle,
			1, 1, 1, 1);
	}
}

//ローディングスレッド
void SceneLoading::LoadingThread(SceneLoading* scene)
{
	//COM関連の初期化でスレッド毎の呼ぶ必要がある
	CoInitialize(nullptr);
	//次のシーンの初期化を行う
	scene->nextScene->Initialize();
	//スレッドが終わる前にCOM関連の終了化
	CoUninitialize();
	//次のシーン完了設定
	scene->nextScene->SetReady();
}

//GUI描画
void SceneLoading::DrawGUI()
{

}