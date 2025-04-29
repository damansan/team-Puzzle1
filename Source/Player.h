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

#ifdef _DEBUG
	void DrawDebugGUI();

#endif


private:
	Model* model = nullptr;
};
