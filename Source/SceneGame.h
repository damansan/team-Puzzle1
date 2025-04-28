#pragma once

#include"Stage.h"
#include"Player.h"
#include"Scene.h"
#include "CameraController.h"

class SceneGame :public Scene
{
public:
	SceneGame() {};
	~SceneGame() override {};

	// ‰Šú‰»
	void Initialize()override;

	// I—¹‰»
	void Finalize()override;

	// XVˆ—
	void Update(float elapsedTime)override;

	// •`‰æˆ—
	void Render()override;

	// GUI•`‰æ
	void DrawGUI()override;

private:
	Stage* stage = nullptr;
	Player* player = nullptr;
	CameraController* cameraController = nullptr;
};
