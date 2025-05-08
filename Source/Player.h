#pragma once

#include "System/ModelRenderer.h"
#include "Character.h"

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

	void InputGridMove();

#ifdef _DEBUG
	void DrawDebugGUI();

#endif

private:
	//�X�e�B�b�N���͒l����ړ��x�N�g�����擾
	DirectX::XMFLOAT3 GetMoveVec()const;

	//�ړ�����
	void Move(float elapsedTime, float vx, float vz, float speed);

	//�ړ����͏���
	void InputMove(float elapsedTime);

	//���񏈗�
	void Turn(float elapsedTime, float vx, float vz, float speed);

private:
	Model* model = nullptr;
	float moveSpeed = 5.0f;
	float turnSpeed = DirectX::XMConvertToRadians(720);

	bool isMoving = false;
	float moveCooldown = 0.0f;
	const float moveInterval = 0.2f;

};
