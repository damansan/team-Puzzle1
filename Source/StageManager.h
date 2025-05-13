#pragma once
#include<vector>
#include"Stage.h"

class StageManager
{
private:
	StageManager() {};
	~StageManager() {};
public:
	static void Generate();

	//唯一のインスタンス取得
	static StageManager& Instance()
	{
		static StageManager instance;
		return instance;
	}

	//更新処理
	void Update(float elapsedTime);
	//描画処理
	void Render(const RenderContext& rc, ModelRenderer* renderer);
	//ステージ登録
	void Register(Stage* stage);
	//ステージ全削除
	void Clear();
	//ステージ取得
	Stage* GetStage(int index) { return stages.at(index); }

private:
	std::vector<Stage*>stages;

};