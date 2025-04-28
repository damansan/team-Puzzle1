#pragma once

#include"System/ModelRenderer.h"
// �X�e�[�W
class Stage
{
public:
	Stage();
	~Stage();

	void Update(float elapsedTime);
	void Render(const RenderContext& rc, ModelRenderer* renderer);

private:
	Model* model = nullptr;

};