#include "Raycast.h"

#include "Raycast.h"
#include <imgui.h>
#include <DirectXCollision.h>


// レイキャスト
bool RayCast(				// 交差したらtrueを返す
	const DirectX::XMFLOAT3& start,		// レイの始点
	const DirectX::XMFLOAT3& end,		// レイの終点
	const DirectX::XMFLOAT3& vertexA,	// 三角形の一つ目の頂点座標
	const DirectX::XMFLOAT3& vertexB,	// 三角形の二つ目の頂点座標
	const DirectX::XMFLOAT3& vertexC,	// 三角形の三つ目の頂点座標
	DirectX::XMFLOAT3& hitPosition,		// 交点の格納先
	DirectX::XMFLOAT3& hitNormal)		// 法線の格納先
{
	//始点と終点レイの単位ベクトルと長さを求める
	DirectX::XMVECTOR Start = DirectX::XMLoadFloat3(&start);
	DirectX::XMVECTOR End = DirectX::XMLoadFloat3(&end);
	DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(End, Start);
	DirectX::XMVECTOR Direction = DirectX::XMVector3Normalize(Vec);
	DirectX::XMVECTOR Length = DirectX::XMVector3Length(Vec);
	float distance = DirectX::XMVectorGetX(Length);

	//三角形の頂点座標
	DirectX::XMVECTOR  A = DirectX::XMLoadFloat3(&vertexA);
	DirectX::XMVECTOR  B = DirectX::XMLoadFloat3(&vertexB);
	DirectX::XMVECTOR  C = DirectX::XMLoadFloat3(&vertexC);

	//DirectXCollisionによるレイと三角形の交差判定
	if (DirectX::TriangleTests::Intersects(Start, Direction, A, B, C, distance))
	{
		//三角形の法線ベクトルを算出
		DirectX::XMVECTOR V1 = DirectX::XMVectorSubtract(B, A);
		DirectX::XMVECTOR V2 = DirectX::XMVectorSubtract(C, A);
		DirectX::XMVECTOR V3 = DirectX::XMVector3Cross(V1, V2);
		V3 = DirectX::XMVector3Normalize(V3);
		DirectX::XMStoreFloat3(&hitNormal, V3);
		//三角形とレイの交点を算出
		DirectX::XMVECTOR hitpoint = DirectX::XMVectorScale(Direction, distance);
		DirectX::XMVECTOR V4 = DirectX::XMVectorAdd(Start, hitpoint);

		//distanceとは当たった場所、だからhitpointは当たった場所と方向を掛ける
		DirectX::XMStoreFloat3(&hitPosition, V4);

		//三角形の裏表判定（表なら交差したと判定する）
		DirectX::XMVECTOR V5 = DirectX::XMVector3Dot(Vec, V3);
		float dot = DirectX::XMVectorGetX(V5);
		return dot < 0;
	}

	return false;
}

