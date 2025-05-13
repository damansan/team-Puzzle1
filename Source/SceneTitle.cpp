#include"System/Graphics.h"
#include"SceneTitle.h"
#include"System/Input.h"
#include"SceneGame.h"
#include"SceneTutorial.h"
#include"SceneManager.h"
#include"SceneLoading.h"
#include"SceneSelect.h"
#include <windows.h>

void SceneTitle::Initialize()
{
	sprite = new Sprite("Data/Sprite/Title.png");
	clicked = false;
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

	HWND hwnd = GetConsoleWindow(); //コンソールアプリで自ウィンドウを取得
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hwnd, &pt);

	//UIButton stageButton(100,40,200,250); // 仮のボタン領域

	if (PtInRect(&stageButton, pt))
	{

		if (width < maxwidth)
		{
			width += 50;
			height += 50;
		}


		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !clicked)
		{
			clicked = true;
			SceneManager::Instance().ChangeScene(new SceneSelect);
		}
	}
	else
	{
		width = orgwidth;
		height = orgheight;
		clicked = false; // ボタンから外れたらリセット
	}

	offsetX = (width - orgwidth) / 2.0f;
	offsetY = (height - orgheight) / 2.0f;

	//GamePad& gamePad = Input::Instance().GetGamePad();
	//
	//const GamePadButton anyButton1 =
	//	GamePad::BTN_A
	//	| GamePad::BTN_B;

	//if (gamePad.GetButtonDown() & anyButton1)
	//{
	//	SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
	//}
	//
	//const GamePadButton anyButton2 =
	//	GamePad::BTN_X
	//	| GamePad::BTN_Y;
	//if (gamePad.GetButtonDown() & anyButton2)
	//{
	//	SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTutorial));
	//}
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
			spriteX - offsetX, spriteY - offsetY, 0, width, height,
			0,
			1, 1, 1, 1);
		//sprite->Render(rc,
		//	0, 0, 0, screenWidth, screenHeight,
		//	0,
		//	1, 1, 1, 1);
	}
}

void SceneTitle::DrawGUI()
{
	RenderContext rc;
	rc.deviceContext = Graphics::Instance().GetDeviceContext();
	rc.renderState = Graphics::Instance().GetRenderState();

	// ボタンの枠の色情報
	float r = 1.0f, g = 0.0f, b = 0.0f, a = 1.0f; // 赤色

	// 上の線
	sprite->Render(rc,
		stageButton.left, stageButton.top, 0,
		stageButton.right - stageButton.left, 1,
		0, r, g, b, a);
	// 下の線
	sprite->Render(rc,
		stageButton.left, stageButton.bottom - 1, 0,
		stageButton.right - stageButton.left, 1,
		0, r, g, b, a);
	// 左の線
	sprite->Render(rc,
		stageButton.left, stageButton.top, 0,
		1, stageButton.bottom - stageButton.top,
		0, r, g, b, a);
	// 右の線
	sprite->Render(rc,
		stageButton.right - 1, stageButton.top, 0,
		1, stageButton.bottom - stageButton.top,
		0, r, g, b, a);
}

