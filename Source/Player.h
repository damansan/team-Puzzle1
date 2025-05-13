#pragma once

#include "System/ModelRenderer.h"
#include "Character.h"

#include "Judge.h"
//プレイヤー
class Player : public Character
{
public:
	Player();
	~Player() override;

	//更新処理
	void Update(float elapsedTime);
	//描画処理
	void Render(const RenderContext& rc, ModelRenderer* renderer);
	//移動処理
	void Move(float elapsedTime, float v, float vz, float speed);
	//移動入力処理
	void InputMove(float elapsedTime);
	//旋回処理
	void Turn(float elapsedTime, float vx, float vz, float speed);
	//デバッグ用GUI描画
	void DrawGUI();
private:
	DirectX::XMFLOAT3 GetMoveVec()const;
	float moveSpeed = 5.0f;
	float turnSpeed = DirectX::XMConvertToRadians(720);
private:
	//プレイヤーとボックスとの衝突判定
	void CollisionPlayerVsBoxs();
private:
	Model* model = nullptr;
private:
	Judge judge;
};
