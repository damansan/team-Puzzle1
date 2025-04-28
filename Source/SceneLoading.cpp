#include"System/Graphics.h"
#include"System/input.h"
#include"SceneLoading.h"
#include"SceneManager.h"

void SceneLoading::Initialize()
{
	sprite = new Sprite("Data/Sprite/LoadingIcon.png");
	thread = new std::thread(LoadingThread, this);
}
void SceneLoading::Finalize()
{
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
	if (thread != nullptr)
	{
		thread->join();
		delete thread;
		thread = nullptr;
	}
}
void SceneLoading::Update(float elapsedTime)
{
	constexpr float speed = 180;
	angle += speed * elapsedTime;

	if (nextScene->IsReady())
	{
		SceneManager::Instance().ChangeScene(nextScene);
		nextScene = nullptr;
	}
}
void SceneLoading::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	RenderState* renderState = graphics.GetRenderState();

	RenderContext rc;
	rc.deviceContext = dc;
	rc.renderState = graphics.GetRenderState();

	{
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
void SceneLoading::LoadingThread(SceneLoading* scene)
{
	CoInitialize(nullptr);
	scene->nextScene->Initialize();
	CoUninitialize();
	scene->nextScene->SetReady();
}
void SceneLoading::DrawGUI()
{

}