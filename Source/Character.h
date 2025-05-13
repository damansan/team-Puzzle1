#pragma once

#include<DirectXMath.h>
#include<imgui.h>
#include"System/ShapeRenderer.h"

//�L�����N�^�[
class Character
{
public:
	Character() {};
	virtual~Character() {};
	
	//�s��X�V����
	void UpdateTransform();

	//���a�擾
	float GetRadius()const { return radius; }
	
	//���l�p�擾
	const DirectX::XMFLOAT3& GethalfSize()const { return halfSize; }
	
	//�f�o�b�O�v���~�e�B�u�`��
	virtual void RenderDebugPrimiteve(const RenderContext& rc, ShapeRenderer* renderer);
protected:
	DirectX::XMFLOAT3 position = { 0,0,0 };
	DirectX::XMFLOAT3 angle = { 0,0,0 };
	DirectX::XMFLOAT3 scale = { 1,1,1 };
	DirectX::XMFLOAT4X4 transform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	float radius = 0.5f;
	DirectX::XMFLOAT3 halfSize = { 0.5f,0.5f,0.5f };
public:
	//�ʒu�擾
	const DirectX::XMFLOAT3& GetPosition()const { return position; }
	//�ʒu�ݒ�
	void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }
	//��]�擾
	const DirectX::XMFLOAT3& GetAngle()const { return angle; }
	//��]�ݒ�
	void SetAngle(const DirectX::XMFLOAT3& angle) { this->angle = angle; }
	//�X�P�[���擾
	const DirectX::XMFLOAT3& GetScale()const { return scale; }
	//�X�P�[���ݒ�
	void SetScale(const DirectX::XMFLOAT3& scale) { this->scale = scale; }
};