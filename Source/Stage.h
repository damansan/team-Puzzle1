#pragma once
#include"System/ModelRenderer.h"
#include"Character.h"

// ステージ
class Stage:public Character
{
public:
	Stage() {};
	//~Stage()override {};
	virtual ~Stage() {};
	//更新処理
	virtual void Update(float elapsedTime) = 0;
	//描画処理
	virtual void Render(const RenderContext& rc, ModelRenderer* renderer) = 0;

};