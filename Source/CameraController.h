#pragma once
#include<DirectXMath.h>
#include <imgui.h>

//カメラコントローラー
class CameraController
{
public:
	//更新処理
	void Update(float elapsedTime);
	//ターゲット位置設定
	void SetTarget(const DirectX::XMFLOAT3& target) { this->target = target; }
	bool CameraMode = false;

private:
	DirectX::XMFLOAT3 target = { 0,0,0 }; //注視点
	DirectX::XMFLOAT3 angle = { 0,0,0 };  //回転角度
	float rollSpeed = DirectX::XMConvertToRadians(90); //回転速度
	float range = 10.0f; //距離
	float maxAngle = DirectX::XMConvertToRadians(85);
	float minAngle = DirectX::XMConvertToRadians(0);

private:
	DirectX::XMFLOAT3 position = { 0,0,0 };
public:
	void DrawGUI();
};