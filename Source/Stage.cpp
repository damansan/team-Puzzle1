#include"Stage.h"

Stage::Stage()
{
	model = new Model("Data/Model/Stage/stage.mdl");
}

Stage:: ~Stage()
{
	delete model;
}

void Stage::Update(float elapsedTime)
{

}

void Stage::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	DirectX::XMFLOAT4X4 transform;
	DirectX::XMStoreFloat4x4(&transform, DirectX::XMMatrixIdentity());
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}