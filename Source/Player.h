#pragma once

#include "System/ModelRenderer.h"
#include "Character.h"

#include "Judge.h"
//�v���C���[
class Player : public Character
{
public:
	Player();
	~Player() override;

	//�X�V����
	void Update(float elapsedTime);
	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* renderer);
	//�ړ�����
	void Move(float elapsedTime, float v, float vz, float speed);
	//�ړ����͏���
	void InputMove(float elapsedTime);
	//���񏈗�
	void Turn(float elapsedTime, float vx, float vz, float speed);
	//�f�o�b�O�pGUI�`��
	void DrawGUI();
private:
	DirectX::XMFLOAT3 GetMoveVec()const;
	float moveSpeed = 5.0f;
	float turnSpeed = DirectX::XMConvertToRadians(720);
private:
	//�v���C���[�ƃ{�b�N�X�Ƃ̏Փ˔���
	void CollisionPlayerVsBoxs();
private:
	Model* model = nullptr;
private:
	Judge judge;
};
