#include"Stage1.h"

//コンストラクタ
Stage1::Stage1()
{
	model = new Model("Data/Model/Stage/Stage.mdl");
	scale.x = scale.y = scale.z = 0.25f;
}

//デストラクタ
Stage1::~Stage1()
{
	delete model;
}

//更新処理
void Stage1::Update(float elapsedTime)
{
	//オブジェクト行列更新
	UpdateTransform();
	//モデル行列更新
	model->UpdateTransform();
}

//描画処理
void Stage1::Render(const RenderContext&rc,ModelRenderer*renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}