#include"StageManager.h"
#include"Stage1.h"
#include"GoalTiles.h"
void StageManager::Generate()
{


	int mapGoal[10][10] =
	{
		{0,0,0},
		{0,1,0}

	};

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (mapGoal[y][x] == 1)
			{
				GoalTiles* goalTiles = new GoalTiles();
				goalTiles->SetPosition(DirectX::XMFLOAT3(0 + 2.5 * x, 1, 0 + 2.5 * -y));
				StageManager::Instance().Register(goalTiles);

			}
		}
	}

///////////////////////////////////////////////////////////////////////////////////////////

	int map1[10][10] =
	{
		{1,1,1},
		{1,0,1}

	};

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (map1[y][x] == 1)
			{
				Stage1* stage1 = new Stage1();
				stage1->SetPosition(DirectX::XMFLOAT3(0 + 2.5 * x, 0, 0 + 2.5 * -y));
				StageManager::Instance().Register(stage1);

			}
		}
	}

	////////////////////////////////////////////////////////////////////////
	

}
//çXêVèàóù
void StageManager::Update(float elapsedTime)
{
	for (Stage* stage : stages)
	{
		stage->Update(elapsedTime);
	}
}

//ï`âÊèàóù
void StageManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	for (Stage* stage : stages)
	{
		stage->Render(rc, renderer);
	}
}

//ÉXÉeÅ[ÉWìoò^
void StageManager::Register(Stage* stage)
{
	stages.emplace_back(stage);
}

void StageManager::Clear()
{
	for (Stage* stage : stages)
	{
		delete stage;
	}
}