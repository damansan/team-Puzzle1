#pragma once
#pragma once
#include"System/Sprite.h"
#include"Scene.h"

class SceneTutorial : public Scene
{
public:
	SceneTutorial() {};
	~SceneTutorial()override {};
	void Initialize()override;
	void Finalize()override;
	void Update(float elapsedTime)override;
	void Render()override;
	void DrawGUI()override;

private:
	Sprite* sprite = nullptr;

};