#pragma once

#include<vector>
#include"Box.h"

//ボックスマネージャー
class BoxManager
{
private:
	BoxManager() {};
	~BoxManager() {};
public:
	//唯一のインスタンス取得
	static void Generate();
	static BoxManager& Instance()
	{
		static BoxManager instance;
		return instance;
	}
	//更新処理
	void Update(float elapsedTime);
	//描画処理
	void Render(const RenderContext& rc, ModelRenderer* renderer);
	//ボックス全削除
	void Clear();
	//ボックス登録
	void Register(Box* box);
	void RenderDebugPrimiteve(const RenderContext& rc, ShapeRenderer* renderer);

private:
	std::vector<Box*>boxs;
};