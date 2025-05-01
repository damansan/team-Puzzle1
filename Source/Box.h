#pragma once
#include"System/ModelRenderer.h"
#include"Character.h"

//ボックス
class Box : public Character
{
public:
	Box() {};
	~Box()override {};

	//更新処理
	virtual void Update(float elapsedTime) = 0;
	//描画処理
	virtual void Render(const RenderContext& rc, ModelRenderer* renderer) = 0;

};