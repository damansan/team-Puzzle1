#include"Character.h"

void Character::UpdateTransform()
{
	// スケール行列を作成
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	// 回転行列を作成
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
	// 位置行列を作成
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	// ３つの行列を組み合わせ、ワールド行列を作成
	DirectX::XMMATRIX W = S * R * T;
	// 計算したワールド行列を取り出す
	DirectX::XMStoreFloat4x4(&transform, W);
}

//デバッグプリミティブ描画
void Character::RenderDebugPrimiteve(const RenderContext& rc, ShapeRenderer* renderer) 
{
	renderer->RenderSphere(rc, position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
}

