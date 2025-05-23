#pragma once

#include"System/Model.h"
#include"Stage.h"

class Stage1 : public Stage
{
public:
	Stage1();
	~Stage1()override;

	//更新処理
	void Update(float elapsedTime)override;
	//描画処理
	void Render(const RenderContext& rc, ModelRenderer* renderer)override;

private:
	Model* model = nullptr;
};