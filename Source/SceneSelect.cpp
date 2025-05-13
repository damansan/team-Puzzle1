#include"System/Graphics.h"
#include"SceneSelect.h"
#include"System/Input.h"
#include"SceneGame.h"
#include"SceneTutorial.h"
#include"SceneManager.h"
#include"SceneLoading.h"
#include <windows.h>

void SceneSelect::Initialize()
{
	sprite = new Sprite("Data/Sprite/Title.png");
	clicked = false;
}

void SceneSelect::Finalize()
{
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void SceneSelect::Update(float elapsedTime)
{

	HWND hwnd = GetConsoleWindow(); //コンソールアプリで自ウィンドウを取得
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hwnd, &pt);


	if (PtInRect(&stageButton1, pt))
	{
		if (width < maxwidth)
		{
			width += 50;
			height += 50;
		}

		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !clicked)
		{
			clicked = true;
			SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
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

}

void SceneSelect::Render()
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
	}
}

void SceneSelect::DrawGUI()
{

}
