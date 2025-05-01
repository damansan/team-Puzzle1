#include"BoxManager.h"
#include"TrueBox.h"

void BoxManager::Generate()
{
	BoxManager& boxManager = BoxManager::Instance();

	int map[10][10] =
	{
		{1,1,1,1,1,1,1,1,1,1 },
		{0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,1,1},
	};

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (map[y][x] == 1)
			{
				TrueBox* trueBox = new TrueBox();
				trueBox->SetPosition(DirectX::XMFLOAT3(0 + x, 0, 0 + y));

				boxManager.Register(trueBox);

			}
		}
	}
}

void BoxManager::Clear()
{
	for (Box* box : boxs)
	{
		delete box;
	}
}

//XVˆ—
void BoxManager::Update(float elapsedTime)
{
	for (Box* box : boxs)
	{
		box->Update(elapsedTime);
	}
}

//•`‰æˆ—
void BoxManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	for (Box* box : boxs)
	{
		box->Render(rc, renderer);
	}
}

//ƒ{ƒbƒNƒX“o˜^
void BoxManager::Register(Box* box)
{
	boxs.emplace_back(box);
}

#ifdef _DEBUG
void BoxManager::RenderDebugPrimiteve(const RenderContext& rc, ShapeRenderer* renderer)
{
	for (Box* box : boxs)
	{
		box->RenderDebugPrimiteve(rc, renderer);
	}
}

#endif 

