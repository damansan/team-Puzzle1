#pragma once
#include"System/Model.h"
#include"Box.h"

//Trueボックス
class TrueBox : public Box
{
public:
	TrueBox();
	~TrueBox()override;

	//更新処理
	void Update(float elapsedTime);
	//描画処理
	void Render(const RenderContext& rc, ModelRenderer* renderer)override;

private:
	Model* model = nullptr;

};