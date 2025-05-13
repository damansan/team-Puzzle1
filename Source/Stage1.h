#pragma once

#include"System/Model.h"
#include"Stage.h"

class Stage1 : public Stage
{
public:
	Stage1();
	~Stage1()override;

	//XVˆ—
	void Update(float elapsedTime)override;
	//•`‰æˆ—
	void Render(const RenderContext& rc, ModelRenderer* renderer)override;

private:
	Model* model = nullptr;
};