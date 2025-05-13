#include"TrueBox.h"

//コンストラクタ
TrueBox::TrueBox()
{
	model = new Model("Data/Model/Moai/moai01.mdl");
	//スケーリング
	scale.x = scale.y = scale.z = 0.1f;
}

//デストラクタ
TrueBox::~TrueBox()
{
	delete model;
}

//更新処理
void TrueBox::Update(float elapsedTime)
{
	//オブジェクト行列更新
	UpdateTransform();
	//モデル行列更新
	model->UpdateTransform();
}

//描画処理
void TrueBox::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}

