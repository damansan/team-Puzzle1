#include"GoalTiles.h"

//コンストラクタ
GoalTiles::GoalTiles()
{
	model = new Model("Data/Model/Stage/Stage.mdl");
	scale.x = scale.y = scale.z = 0.25f;
}

//デストラクタ
GoalTiles::~GoalTiles()
{
	delete model;
}

//こうしんしょり
void GoalTiles::Update(float elapsedTime)
{
	//オブジェクト行列更新
	UpdateTransform();
	//モデル行列更新
	model->UpdateTransform();

}

//描画処理
void GoalTiles::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}
