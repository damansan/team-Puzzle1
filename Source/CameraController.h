#pragma once
#include<DirectXMath.h>
#include <imgui.h>

//�J�����R���g���[���[
class CameraController
{
public:
	//�X�V����
	void Update(float elapsedTime);
	//�^�[�Q�b�g�ʒu�ݒ�
	void SetTarget(const DirectX::XMFLOAT3& target) { this->target = target; }
	bool CameraMode = false;

private:
	DirectX::XMFLOAT3 target = { 0,0,0 }; //�����_
	DirectX::XMFLOAT3 angle = { 0,0,0 };  //��]�p�x
	float rollSpeed = DirectX::XMConvertToRadians(90); //��]���x
	float range = 10.0f; //����
	float maxAngle = DirectX::XMConvertToRadians(85);
	float minAngle = DirectX::XMConvertToRadians(0);

private:
	DirectX::XMFLOAT3 position = { 0,0,0 };
public:
	void DrawGUI();
};