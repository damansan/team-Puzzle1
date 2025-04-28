#pragma once

#include <DirectXMath.h>

class CameraController
{
public:
	//�X�V����
	void Update(float elapsedTime);

	//�^�[�Q�b�g�ʒu�m�F
	void SeTarget(const DirectX::XMFLOAT3& target) { this->target = target; }

private:
	DirectX::XMFLOAT3 target = { 0,0,0 };
	DirectX::XMFLOAT3 angle  = { 0,0,0 };
	float rollSpeed = DirectX::XMConvertToRadians(90);
	float range = 10.0f;
	float maxAngleX = DirectX::XMConvertToRadians(45);
	float minAngleX = DirectX::XMConvertToRadians(-45);
};