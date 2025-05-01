#include"TrueBox.h"

TrueBox::TrueBox()
{
	model = new Model("Data/Model/Slime/Slime.mdl");
	scale.x = scale.y = scale.z = 0.01f;
}

TrueBox::~TrueBox()
{
	delete model;
}

void TrueBox::Update(float elapsedTime)
{
	UpdateTransform();
	model->UpdateTransform();
}

void TrueBox::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}