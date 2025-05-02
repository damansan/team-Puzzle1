#include"TrueBox.h"

//コンストラクタ
TrueBox::TrueBox()
{
	model = new Model("Data/Model/Slime/Slime.mdl");
	//スケーリング
	scale.x = scale.y = scale.z = 0.01f;
}

//デストラクタ
TrueBox::~TrueBox()
{
	delete model;
}

//更新処理
void TrueBox::Update(float elapsedTime)
{
	UpdateTransform();
	model->UpdateTransform();
}

//描画処理
void TrueBox::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}