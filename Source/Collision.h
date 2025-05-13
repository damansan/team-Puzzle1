#pragma once
#include<DirectXMath.h>
#include"System/Model.h"

class Collision
{
public:
	//���Ƌ��̌�������
	static bool InstersectSpherVsSphere(
		const DirectX::XMFLOAT3& positionA,
		float radiusA,
		const DirectX::XMFLOAT3& positionB,
		float radiusB,
		DirectX::XMFLOAT3& outPositionB);

	//�l�p�Ǝl�p�̌�������
	static bool IntersectAndPushBoxVSBox(
		const DirectX::XMFLOAT3& positionA,
		const DirectX::XMFLOAT3& halfSizeA,
		const DirectX::XMFLOAT3& positionB,
		const DirectX::XMFLOAT3& halfSizeB,
		DirectX::XMFLOAT3& outPositionB
	);

	// ���C�L���X�g
	static bool RayCast(
		const DirectX::XMFLOAT3& start,
		const DirectX::XMFLOAT3& end,
		const DirectX::XMFLOAT4X4& worldTransform,
		const Model* model,
		DirectX::XMFLOAT3& hitPosition,
		DirectX::XMFLOAT3& hitNormal);

};