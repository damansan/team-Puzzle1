#include "Camera.h"

//�w�����������
void Camera::SetLookAt(const DirectX::XMFLOAT3& eye, const DirectX::XMFLOAT3 focus, const DirectX::XMFLOAT3& up)
{
	//�n�_�A���ӓ_�A���������r���[�s����쐬
	DirectX::XMVECTOR Eye   = DirectX::XMLoadFloat3(&eye);
	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	DirectX::XMVECTOR Up    = DirectX::XMLoadFloat3(&up);
	DirectX::XMMATRIX View  = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
	DirectX::XMStoreFloat4x4(&view, View);
}


//�o�[�X�؃N�e�B�u�ݒ�
void Camera::SetPerspectiveFov(float fovY, float aspect, float nearZ, float farZ)
{
	//�摜�A�摜�䗦�A�N���b�v��������v���W�F�N�V�����s����쐬
	DirectX::XMMATRIX Projection= DirectX::XMMatrixPerspectiveFovLH(fovY, aspect, nearZ, farZ);
 
	DirectX::XMStoreFloat4x4(&projection, Projection);
}


