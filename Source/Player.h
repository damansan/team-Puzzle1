#pragma once

#include "System/ModelRenderer.h"
#include "Character.h"

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

	void InputGridMove();

#ifdef _DEBUG
	void DrawDebugGUI();

#endif

private:
	//スティック入力値から移動ベクトルを取得
	DirectX::XMFLOAT3 GetMoveVec()const;

	//移動処理
	void Move(float elapsedTime, float vx, float vz, float speed);

	//移動入力処理
	void InputMove(float elapsedTime);

	//旋回処理
	void Turn(float elapsedTime, float vx, float vz, float speed);

private:
	Model* model = nullptr;
	float moveSpeed = 5.0f;
	float turnSpeed = DirectX::XMConvertToRadians(720);

	bool isMoving = false;
	float moveCooldown = 0.0f;
	const float moveInterval = 0.2f;

};
