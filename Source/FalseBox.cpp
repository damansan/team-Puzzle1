#include"FalseBox.h"

//コンストラクタ
FalseBox::FalseBox()
{
	model = new Model("Data/Model/Slime/Slime.mdl");
	//スケーリング
	scale.x = scale.y = scale.z = 0.01f;
}

//デストラクタ
FalseBox::~FalseBox()
{
	delete model;
}

//更新処理
void FalseBox::Update(float elapsedTime)
{
	//オブジェクト行列更新
	UpdateTransform();
	//モデル行列更新
	model->UpdateTransform();
}

//描画処理
void FalseBox::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}

