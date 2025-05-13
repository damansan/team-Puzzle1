#pragma once

#include"System/Model.h"
#include"Stage.h"

class GoalTiles :public Stage
{
public:
	GoalTiles();
	~GoalTiles()override;

	//XVˆ—
	void Update(float elapsedTime);
	//•`‰æˆ—
	void Render(const RenderContext& rc, ModelRenderer* renderer)override;

private:
	Model* model = nullptr;

};