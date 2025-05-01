#pragma once
#include"System/Model.h"
#include"Box.h"

class TrueBox : public Box
{
public:
	TrueBox();
	~TrueBox()override;

	void Update(float elapsedTime);
	void Render(const RenderContext& rc, ModelRenderer* renderer)override;

private:
	Model* model = nullptr;

};