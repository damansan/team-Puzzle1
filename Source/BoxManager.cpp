#include"BoxManager.h"
#include"TrueBox.h"
#include"FalseBox.h"
#include"Collision.h"

void BoxManager::Generate()
{

	//TrueBox�̈ʒu���}�b�v�`�b�v�Ŕz�u
	int True[10][10] =
	{
		{1,0,0,0,0,0,0,0,0,0},
	};

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10 ; x++)
		{
			//�}�b�v�`�b�v��1�̂�����ɃI�u�W�F�N�g��z�u
			if (True[y][x]==1)
			{
				TrueBox* trueBox = new TrueBox();
				trueBox->SetPosition(DirectX::XMFLOAT3(0 + x, 0, 0 - y));
				//�{�b�N�X�ɓo�^
				BoxManager::Instance().Register(trueBox);
			}
		}
//////////////////////////////////////////////////////////////////////////////////
		
		//FalseBox�̈ʒu���}�b�v�`�b�v�Ŕz�u
		int Fales[10][10] =
		{
			{0,1,0,0,0,0,0,0,0,0},

		};

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				//�}�b�v�`�b�v��1�̂�����ɃI�u�W�F�N�g��z�u
				if (Fales[y][x] == 1)
				{
					FalseBox* falseBox = new FalseBox();
					falseBox->SetPosition(DirectX::XMFLOAT3(0 + x, 0, 0 - y));
					//�{�b�N�X��o�^
					BoxManager::Instance().Register(falseBox);

				}
			}
		}

	}
}

//�{�b�N�X�S�폜
void BoxManager::Clear()
{
	for (Box* box : boxs)
	{
		delete box;
	}
}

//�X�V����
void BoxManager::Update(float elapsedTime)
{
	for (Box* box : boxs)
	{
		box->Update(elapsedTime);
	}
	//CollisionBoxVsBoxs();
}

//�`�揈��
void BoxManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	for (Box* box : boxs)
	{
		box->Render(rc, renderer);
	}
}

//�{�b�N�X�o�^
void BoxManager::Register(Box* box)
{
	boxs.emplace_back(box);
}

#ifdef _DEBUG
//�f�o�b�O�v���~�e�B�u�`��
void BoxManager::RenderDebugPrimiteve(const RenderContext& rc, ShapeRenderer* renderer)
{
	for (Box* box : boxs)
	{
		box->RenderDebugPrimiteve(rc, renderer);
	}
}

#endif 

