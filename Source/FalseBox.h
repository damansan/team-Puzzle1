#pragma once
#include"System/Model.h"
#include"Box.h"

//Falseボックス
class FalseBox : public Box
{
public:
	FalseBox();
	~FalseBox()override;

	//更新処理
	void Update(float elapsedTime)override;
	//描画処理
	void Render(const RenderContext& rc, ModelRenderer* renderer)override;
private:
	Model* model = nullptr;

};