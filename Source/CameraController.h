#pragma once

#include <DirectXMath.h>

class CameraController
{
public:
	//更新処理
	void Update(float elapsedTime);

	//ターゲット位置確認
	void SeTarget(const DirectX::XMFLOAT3& target) { this->target = target; }

private:
	DirectX::XMFLOAT3 target = { 0,0,0 };
	DirectX::XMFLOAT3 angle  = { 0,0,0 };
	float rollSpeed = DirectX::XMConvertToRadians(90);
	float range = 10.0f;
	float maxAngleX = DirectX::XMConvertToRadians(45);
	float minAngleX = DirectX::XMConvertToRadians(-45);
};