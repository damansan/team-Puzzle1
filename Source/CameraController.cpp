#include"System/Input.h"
#include"CameraController.h"
#include"Camera.h"

//�X�V����
void CameraController::Update(float elapsedTime)
{
	if (!CameraMode)
	{
		GamePad& gamePad = Input::Instance().GetGamePad();
		float ax = gamePad.GetAxisRX();
		float ay = gamePad.GetAxisRY();
		//�J������]���x
		float speed = rollSpeed * elapsedTime;
		//�X�e�B�b�N���͂ɍ��킹��X��Y�����J�X
		angle.x += ay * speed;
		angle.y += ax * speed;
		//�J������]�l����]�s��ɕϊ�
		DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

		//��]�s�񂩂�O�����x�N�g�������o��
		DirectX::XMVECTOR Front = Transform.r[2];
		DirectX::XMFLOAT3 front;
		DirectX::XMStoreFloat3(&front, Front);

		//�����_������x�N�g���Ɉ��������ꂽ�J���������n�_�����߂�
		DirectX::XMFLOAT3 eye;
		eye.x = target.x - front.x * range;
		eye.y = target.y - front.y * range;
		eye.z = target.z - front.z * range;

		//X���J������]�𐧌�
		if (angle.x > maxAngle)
		{
			angle.x = maxAngle;
		}
		if (angle.x < minAngle)
		{
			angle.x = minAngle;
		}
		//Y���̉�]���l��-3.14�`3.14�Ɏ��߂�
		if (angle.y < -DirectX::XM_PI)
		{
			angle.y += DirectX::XM_2PI;
		}
		if (angle.y > DirectX::XM_PI)
		{
			angle.y -= DirectX::XM_2PI;
		}
		//�J�����̎��_�ƒ����_��ݒ�
		Camera::Instance().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
	}

	if (CameraMode)
	{
			GamePad& gamePad = Input::Instance().GetGamePad();
			float ax = gamePad.GetAxisRX();
			float ay = gamePad.GetAxisRY();
			float moveSpeed = 5.0f * elapsedTime;
			position.x += ax * moveSpeed;
			position.z += ay * moveSpeed;

			const GamePadButton anyButton1 = GamePad::BTN_A;
			if (gamePad.GetButton() & anyButton1)
			{
				position.y += moveSpeed;
			}
			const GamePadButton anyButton2 = GamePad::BTN_B;
			if (gamePad.GetButton() & anyButton2)
			{
				position.y -= moveSpeed;
			}

		DirectX::XMFLOAT3 focus = { position.x, position.y, position.z + 1.0f };
		Camera::Instance().SetLookAt(position, focus, DirectX::XMFLOAT3(0, 1, 0));
	}
	
}

#ifdef _DEBUG
void CameraController::DrawGUI()
{
	ImGui::Begin("CameraController");

	DirectX::XMFLOAT3 a;
	a.x = DirectX::XMConvertToDegrees(angle.x);
	a.y = DirectX::XMConvertToDegrees(angle.y);
	a.z = DirectX::XMConvertToDegrees(angle.z);
	ImGui::Text("Camera Angle: X: %.2f  Y: %.2f  Z: %.2f", a.x, a.y, a.z);


	DirectX::XMFLOAT3 p;
	p.x = DirectX::XMConvertToDegrees(position.x);
	p.y = DirectX::XMConvertToDegrees(position.y);
	p.z = DirectX::XMConvertToDegrees(position.z);
	ImGui::Text("Camera Position: X: %.2f  Y: %.2f  Z: %.2f", p.x, p.y, p.z);

	ImGui::Checkbox("FreePosition", &CameraMode);

	ImGui::End();
}
#endif 