#pragma once

#include<set>
#include<vector>
#include"Box.h"

//ボックスマネージャー
class BoxManager
{
private:
	BoxManager() {};
	~BoxManager() {};
public:
	static void Generate();
	
	//唯一のインスタンス取得
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
	//デバッグプリミティブ描画
	void RenderDebugPrimiteve(const RenderContext& rc, ShapeRenderer* renderer);
	//ボックス数取得
	int GetBoxCount()const { return static_cast<int>(boxs.size()); }
	//ボックス取得
	Box* GetBox(int index) { return boxs.at(index); }

private:
	std::vector<Box*>boxs;
};