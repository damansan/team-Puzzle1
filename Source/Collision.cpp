#include<DirectXCollision.h>
#include"Collision.h"

//���Ƌ��̌�������
bool Collision::InstersectSpherVsSphere(
	const DirectX::XMFLOAT3& positionA,
	float radiusA,
	const DirectX::XMFLOAT3& positionB,
	float radiusB,
	DirectX::XMFLOAT3& outPositionB)
{
	//A��B�̒P�ʃx�N�g���Z�o
	DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat3(&positionA);
	DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat3(&positionB);
	DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(PositionB, PositionA);
	DirectX::XMVECTOR LengthSq = DirectX::XMVector3LengthSq(Vec);
	float lengthSq;
	DirectX::XMStoreFloat(&lengthSq, LengthSq);

	//��������
	float range = radiusA + radiusB;
	if (lengthSq > range*range)
	{
		return false;
	}

	//A��B�������o��
	Vec = DirectX::XMVector3Normalize(Vec);
	Vec = DirectX::XMVectorScale(Vec, range);
	PositionB = DirectX::XMVectorAdd(PositionA, Vec);
	DirectX::XMStoreFloat3(&outPositionB, PositionB);
	return true;
}

bool Collision::IntersectAndPushBoxVSBox(
	const DirectX::XMFLOAT3& positionA,
	const DirectX::XMFLOAT3& halfSizeA,
	const DirectX::XMFLOAT3& positionB,
	const DirectX::XMFLOAT3& halfSizeB,
	DirectX::XMFLOAT3& outPositionB)
{
	float dx = positionB.x - positionA.x;
	float dy = positionB.y - positionA.y;
	float dz = positionB.z - positionA.z;

	// �����Ƃ̏d�Ȃ���v�Z
	float overlapX = (halfSizeA.x + halfSizeB.x) - std::abs(dx);
	float overlapY = (halfSizeA.y + halfSizeB.y) - std::abs(dy);
	float overlapZ = (halfSizeA.z + halfSizeB.z) - std::abs(dz);

	// �d�Ȃ��Ă��Ȃ���ΏՓ˂��Ă��Ȃ�
	if (overlapX <= 0.0f || overlapY <= 0.0f || overlapZ <= 0.0f)
	{
		return false;
	}
	outPositionB = positionB; // �����͂��̂܂�

	if (overlapX < overlapY && overlapX < overlapZ)
	{
		outPositionB.x += (dx > 0.0f) ? overlapX : -overlapX;
	}
	else if (overlapY < overlapZ)
	{
		outPositionB.y += (dy > 0.0f) ? overlapY : -overlapY;
	}
	else
	{
		outPositionB.z += (dz > 0.0f) ? overlapZ : -overlapZ;
	}

	return true;
}

//���C�L���X�g
bool Collision::RayCast(
	const DirectX::XMFLOAT3& start,
	const DirectX::XMFLOAT3& end,
	const DirectX::XMFLOAT4X4& worldTransform,
	const Model* model,
	DirectX::XMFLOAT3& hitPosition,
	DirectX::XMFLOAT3& hitNormal)
{
	bool hit = false;

	// �n�_�ƏI�_���烌�C�̃x�N�g���ƒ��������߂�
	DirectX::XMVECTOR WorldRayStart = DirectX::XMLoadFloat3(&start);
	DirectX::XMVECTOR WorldRayEnd = DirectX::XMLoadFloat3(&end);
	DirectX::XMVECTOR WorldRayVec = DirectX::XMVectorSubtract(WorldRayEnd, WorldRayStart);
	DirectX::XMVECTOR WorldRayLength = DirectX::XMVector3Length(WorldRayVec);

	float nearestDist = DirectX::XMVectorGetX(WorldRayLength);
	if (nearestDist <= 0.0f) return false;

	DirectX::XMMATRIX ParentWorldTransform = DirectX::XMLoadFloat4x4(&worldTransform);

	// ���f�����̑S�Ẵ��b�V���ƌ���������s��
	const ModelResource* resource = model->GetResource();
	for (const ModelResource::Mesh& mesh : resource->GetMeshes())
	{
		// ���b�V���̃��[���h�s������߂�
		const Model::Node& node = model->GetNodes().at(mesh.nodeIndex);
		DirectX::XMMATRIX GlobalTransform = DirectX::XMLoadFloat4x4(&node.globalTransform);
		DirectX::XMMATRIX WorldTransform = DirectX::XMMatrixMultiply(GlobalTransform, ParentWorldTransform);

		// ���C�����b�V���̃��[�J����Ԃɕϊ�����
		DirectX::XMMATRIX InverseWorldTransform = DirectX::XMMatrixInverse(nullptr, WorldTransform);
		DirectX::XMVECTOR LocalRayStart = DirectX::XMVector3Transform(WorldRayStart, InverseWorldTransform);
		DirectX::XMVECTOR LocalRayEnd = DirectX::XMVector3Transform(WorldRayEnd, InverseWorldTransform);
		DirectX::XMVECTOR LocalRayVec = DirectX::XMVectorSubtract(LocalRayEnd, LocalRayStart);
		DirectX::XMVECTOR LocalRayDirection = DirectX::XMVector3Normalize(LocalRayVec);
		float distance = DirectX::XMVectorGetX(DirectX::XMVector3Length(LocalRayVec));

		// ���b�V�����̑S�Ă̎O�p�`�ƌ���������s��
		for (size_t i = 0; i < mesh.indices.size(); i += 3)
		{
			// �O�p�`�̒��_���W���擾
			const ModelResource::Vertex& a = mesh.vertices.at(mesh.indices.at(i + 0));
			const ModelResource::Vertex& b = mesh.vertices.at(mesh.indices.at(i + 1));
			const ModelResource::Vertex& c = mesh.vertices.at(mesh.indices.at(i + 2));

			DirectX::XMVECTOR A = DirectX::XMLoadFloat3(&a.position);
			DirectX::XMVECTOR B = DirectX::XMLoadFloat3(&b.position);
			DirectX::XMVECTOR C = DirectX::XMLoadFloat3(&c.position);

			// �O�p�`�̌�������
			if (DirectX::TriangleTests::Intersects(LocalRayStart, LocalRayDirection, A, B, C, distance))
			{
				// ���b�V���̃��[�J����Ԃł̌�_�����߂�
				DirectX::XMVECTOR LocalHitVec = DirectX::XMVectorScale(LocalRayDirection, distance);
				DirectX::XMVECTOR LocalHitPosition = DirectX::XMVectorAdd(LocalRayStart, LocalHitVec);

				// ���b�V���̃��[�J����Ԃł̌�_�����[���h��Ԃɕϊ�����
				DirectX::XMVECTOR WorldHitPosition = DirectX::XMVector3Transform(LocalHitPosition, WorldTransform);

				// ���[���h��Ԃł̃��C�̎n�_�����_�܂ł̋��������߂�
				DirectX::XMVECTOR WorldHitVec = DirectX::XMVectorSubtract(WorldHitPosition, WorldRayStart);
				DirectX::XMVECTOR WorldHitDist = DirectX::XMVector3Length(WorldHitVec);
				float worldHitDist = DirectX::XMVectorGetX(WorldHitDist);

				// ��_�܂ł̋��������܂łɌv�Z������_���߂��ꍇ�͌��������Ɣ��肷��
				if (worldHitDist <= nearestDist)
				{
					// ���b�V���̃��[�J����Ԃł̎O�p�`�̖@���x�N�g�����Z�o
					DirectX::XMVECTOR AB = DirectX::XMVectorSubtract(B, A);
					DirectX::XMVECTOR BC = DirectX::XMVectorSubtract(C, B);
					DirectX::XMVECTOR LocalHitNormal = DirectX::XMVector3Cross(AB, BC);

					// ���b�V���̃��[�J����Ԃł̖@���x�N�g�������[���h��Ԃɕϊ�����
					DirectX::XMVECTOR WorldHitNormal = DirectX::XMVector3TransformNormal(LocalHitNormal, WorldTransform);

					// �O�p�`�̗��\����i���ς̌��ʂ��}�C�i�X�Ȃ�Ε\�����j
					DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(LocalRayDirection, LocalHitNormal);
					float dot = DirectX::XMVectorGetX(Dot);
					if (dot < 0)
					{
						// ���������̂Ńq�b�g�����i�[
						DirectX::XMStoreFloat3(&hitNormal, DirectX::XMVector3Normalize(WorldHitNormal));
						DirectX::XMStoreFloat3(&hitPosition, WorldHitPosition);

						// ��_�܂ł̋������X�V����
						nearestDist = worldHitDist;
						hit = true;
					}
				}
			}
		}
	}
	return hit;

}