#include"System/Input.h"
#include"CameraController.h"
#include"Camera.h"

//更新処理
void CameraController::Update(float elapsedTime)
{
	if (!CameraMode)
	{
		GamePad& gamePad = Input::Instance().GetGamePad();
		float ax = gamePad.GetAxisRX();
		float ay = gamePad.GetAxisRY();
		//カメラ回転速度
		float speed = rollSpeed * elapsedTime;
		//スティック入力に合わせてX軸Y軸を開店
		angle.x += ay * speed;
		angle.y += ax * speed;
		//カメラ回転値を回転行列に変換
		DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

		//回転行列から前方向ベクトルを取り出す
		DirectX::XMVECTOR Front = Transform.r[2];
		DirectX::XMFLOAT3 front;
		DirectX::XMStoreFloat3(&front, Front);

		//注視点から後ろベクトルに一定方向離れたカメラ方向始点を求める
		DirectX::XMFLOAT3 eye;
		eye.x = target.x - front.x * range;
		eye.y = target.y - front.y * range;
		eye.z = target.z - front.z * range;

		//X軸カメラ回転を制御
		if (angle.x > maxAngle)
		{
			angle.x = maxAngle;
		}
		if (angle.x < minAngle)
		{
			angle.x = minAngle;
		}
		//Y軸の回転数値を-3.14～3.14に収める
		if (angle.y < -DirectX::XM_PI)
		{
			angle.y += DirectX::XM_2PI;
		}
		if (angle.y > DirectX::XM_PI)
		{
			angle.y -= DirectX::XM_2PI;
		}
		//カメラの視点と注視点を設定
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