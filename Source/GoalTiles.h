#pragma once

#include"System/Model.h"
#include"Stage.h"

class GoalTiles :public Stage
{
public:
	GoalTiles();
	~GoalTiles()override;

	//�X�V����
	void Update(float elapsedTime);
	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* renderer)override;

private:
	Model* model = nullptr;

};