#pragma once

#include"System/Model.h"
#include"Stage.h"

class GoalTiles :public Stage
{
public:
	GoalTiles();
	~GoalTiles()override;

	//更新処理
	void Update(float elapsedTime);
	//描画処理
	void Render(const RenderContext& rc, ModelRenderer* renderer)override;

private:
	Model* model = nullptr;

};