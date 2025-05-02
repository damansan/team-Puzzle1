#include "Raycast.h"

#include "Raycast.h"
#include <imgui.h>
#include <DirectXCollision.h>


// ���C�L���X�g
bool RayCast(				// ����������true��Ԃ�
	const DirectX::XMFLOAT3& start,		// ���C�̎n�_
	const DirectX::XMFLOAT3& end,		// ���C�̏I�_
	const DirectX::XMFLOAT3& vertexA,	// �O�p�`�̈�ڂ̒��_���W
	const DirectX::XMFLOAT3& vertexB,	// �O�p�`�̓�ڂ̒��_���W
	const DirectX::XMFLOAT3& vertexC,	// �O�p�`�̎O�ڂ̒��_���W
	DirectX::XMFLOAT3& hitPosition,		// ��_�̊i�[��
	DirectX::XMFLOAT3& hitNormal)		// �@���̊i�[��
{
	//�n�_�ƏI�_���C�̒P�ʃx�N�g���ƒ��������߂�
	DirectX::XMVECTOR Start = DirectX::XMLoadFloat3(&start);
	DirectX::XMVECTOR End = DirectX::XMLoadFloat3(&end);
	DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(End, Start);
	DirectX::XMVECTOR Direction = DirectX::XMVector3Normalize(Vec);
	DirectX::XMVECTOR Length = DirectX::XMVector3Length(Vec);
	float distance = DirectX::XMVectorGetX(Length);

	//�O�p�`�̒��_���W
	DirectX::XMVECTOR  A = DirectX::XMLoadFloat3(&vertexA);
	DirectX::XMVECTOR  B = DirectX::XMLoadFloat3(&vertexB);
	DirectX::XMVECTOR  C = DirectX::XMLoadFloat3(&vertexC);

	//DirectXCollision�ɂ�郌�C�ƎO�p�`�̌�������
	if (DirectX::TriangleTests::Intersects(Start, Direction, A, B, C, distance))
	{
		//�O�p�`�̖@���x�N�g�����Z�o
		DirectX::XMVECTOR V1 = DirectX::XMVectorSubtract(B, A);
		DirectX::XMVECTOR V2 = DirectX::XMVectorSubtract(C, A);
		DirectX::XMVECTOR V3 = DirectX::XMVector3Cross(V1, V2);
		V3 = DirectX::XMVector3Normalize(V3);
		DirectX::XMStoreFloat3(&hitNormal, V3);
		//�O�p�`�ƃ��C�̌�_���Z�o
		DirectX::XMVECTOR hitpoint = DirectX::XMVectorScale(Direction, distance);
		DirectX::XMVECTOR V4 = DirectX::XMVectorAdd(Start, hitpoint);

		//distance�Ƃ͓��������ꏊ�A������hitpoint�͓��������ꏊ�ƕ������|����
		DirectX::XMStoreFloat3(&hitPosition, V4);

		//�O�p�`�̗��\����i�\�Ȃ���������Ɣ��肷��j
		DirectX::XMVECTOR V5 = DirectX::XMVector3Dot(Vec, V3);
		float dot = DirectX::XMVectorGetX(V5);
		return dot < 0;
	}

	return false;
}

