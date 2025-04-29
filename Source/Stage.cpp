#include"Stage.h"

//コンストラクタ
Stage::Stage()
{
	model = new Model("Data/Model/Stage/stage.mdl");
}

//デストラクタ
Stage:: ~Stage()
{
	delete model;
}

//更新処理
void Stage::Update(float elapsedTime)
{

}

//描画処理
void Stage::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	DirectX::XMFLOAT4X4 transform;
	DirectX::XMStoreFloat4x4(&transform, DirectX::XMMatrixIdentity());
	//レンダラにモデル描画してもらう
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}