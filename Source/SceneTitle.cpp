#include"System/Graphics.h"
#include"SceneTitle.h"
#include"System/Input.h"
#include"SceneGame.h"
#include"SceneTutorial.h"
#include"SceneManager.h"
#include"SceneLoading.h"
void SceneTitle::Initialize()
{
	sprite = new Sprite("Data/Sprite/Title.png");
}

void SceneTitle::Finalize()
{
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void SceneTitle::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	
	const GamePadButton anyButton1 =
		GamePad::BTN_A
		| GamePad::BTN_B;

	if (gamePad.GetButtonDown() & anyButton1)
	{
		SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
	}
	
	const GamePadButton anyButton2 =
		GamePad::BTN_X
		| GamePad::BTN_Y;
	if (gamePad.GetButtonDown() & anyButton2)
	{
		SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTutorial));
	}
}

void SceneTitle::Render()
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
		sprite->Render(rc,
			0, 0, 0, screenWidth, screenHeight,
			0,
			1, 1, 1, 1);
	}
}

void SceneTitle::DrawGUI() 
{

}

