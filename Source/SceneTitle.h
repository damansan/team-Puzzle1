#pragma once
#include"System/Sprite.h"
#include"Scene.h"

class SceneTitle : public Scene
{
public:
	SceneTitle() {};
	~SceneTitle()override {};
	void Initialize()override;
	void Finalize()override;
	void Update(float elapsedTime)override;
	void Render()override;
	void DrawGUI()override;

private:
	Sprite* sprite = nullptr;
	bool clicked = false;

	float spriteX = 100;
	float spriteY = 40;
	int width = 200;
	int height = 150;
	int maxwidth = width + 50;

	int orgwidth = width;
	int orgheight = height;

	//sprite�g�厞�ʒu������邽�ߏ㉺���E�ϓ��Ɋg��ł���悤�ɂ���ϐ�
	float offsetX;
	float offsetY;


	//�����蔻��p�̍��W�ɂ��ꂪ���邽�ߕ␳
	float RECTX = spriteX + 100;
	float RECTY = spriteY + 70;
	int RECTwidth = width;
	int RECTheight = height - 60;

	RECT stageButton =
	{
	   static_cast<LONG>(RECTX - RECTwidth / 2),
	   static_cast<LONG>(RECTY - RECTheight / 2),
	   static_cast<LONG>(RECTX + RECTwidth / 2),
	   static_cast<LONG>(RECTY + RECTheight / 2)
	};

};