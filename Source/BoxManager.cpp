#include"BoxManager.h"
#include"TrueBox.h"
#include"FalseBox.h"
#include"Collision.h"

void BoxManager::Generate()
{

	//TrueBoxの位置をマップチップで配置
	int True[10][10] =
	{
		{1,0,0,0,0,0,0,0,0,0},
	};

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10 ; x++)
		{
			//マップチップに1のある個所にオブジェクトを配置
			if (True[y][x]==1)
			{
				TrueBox* trueBox = new TrueBox();
				trueBox->SetPosition(DirectX::XMFLOAT3(0 + x, 0, 0 - y));
				//ボックスに登録
				BoxManager::Instance().Register(trueBox);
			}
		}
//////////////////////////////////////////////////////////////////////////////////
		
		//FalseBoxの位置をマップチップで配置
		int Fales[10][10] =
		{
			{0,1,0,0,0,0,0,0,0,0},

		};

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				//マップチップに1のある個所にオブジェクトを配置
				if (Fales[y][x] == 1)
				{
					FalseBox* falseBox = new FalseBox();
					falseBox->SetPosition(DirectX::XMFLOAT3(0 + x, 0, 0 - y));
					//ボックスを登録
					BoxManager::Instance().Register(falseBox);

				}
			}
		}

	}
}

//ボックス全削除
void BoxManager::Clear()
{
	for (Box* box : boxs)
	{
		delete box;
	}
}

//更新処理
void BoxManager::Update(float elapsedTime)
{
	for (Box* box : boxs)
	{
		box->Update(elapsedTime);
	}
	//CollisionBoxVsBoxs();
}

//描画処理
void BoxManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	for (Box* box : boxs)
	{
		box->Render(rc, renderer);
	}
}

//ボックス登録
void BoxManager::Register(Box* box)
{
	boxs.emplace_back(box);
}

#ifdef _DEBUG
//デバッグプリミティブ描画
void BoxManager::RenderDebugPrimiteve(const RenderContext& rc, ShapeRenderer* renderer)
{
	for (Box* box : boxs)
	{
		box->RenderDebugPrimiteve(rc, renderer);
	}
}

#endif 

