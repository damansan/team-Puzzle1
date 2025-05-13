#pragma once
#include"TrueBox.h"
#include"GoalTiles.h"
#include"BoxManager.h"
#include"StageManager.h"

class Judge
{
public:
	Judge() {};
	~Judge() {};
	
	void GetPosition();
	void DrawGUI();

	bool GoalFlag = false;
private:
	
};