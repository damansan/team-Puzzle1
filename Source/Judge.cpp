#include"Judge.h"

void Judge::GetPosition()
{
    //TrueBoxとGoalTilesのポインタを取得
    TrueBox* trueBox = dynamic_cast<TrueBox*>(BoxManager::Instance().GetBox(0));
    GoalTiles* goalTiles = dynamic_cast<GoalTiles*>(StageManager::Instance().GetStage(0));

    //ポジションをGetし変数に入れる
    DirectX::XMFLOAT3 PosT = trueBox->GetPosition();
    DirectX::XMFLOAT3 PosG = goalTiles->GetPosition();


    //ゴール判定
    if (PosT.x < PosG.x)
    {
        GoalFlag = true;
    }
    else
    {
        GoalFlag = false;
    }
}


void Judge::DrawGUI()
{

    ImGui::Begin("Judge");

    //TrueBoxとGoalTilesのポインタを取得
    TrueBox* trueBox = dynamic_cast<TrueBox*>(BoxManager::Instance().GetBox(0));
    GoalTiles* goalTiles = dynamic_cast<GoalTiles*>(StageManager::Instance().GetStage(0));

    if (trueBox)
    {
        DirectX::XMFLOAT3 boxPos = trueBox->GetPosition();
        ImGui::Text("TrueBox Position: X: %.2f  Y: %.2f  Z: %.2f", boxPos.x, boxPos.y, boxPos.z);

    }
    else
    {
        ImGui::Text("TrueBox not found.");
    }

    if (goalTiles)
    {
        DirectX::XMFLOAT3 goalPos = goalTiles->GetPosition();
        ImGui::Text("GoalTiles Position: X: %.2f  Y: %.2f  Z: %.2f", goalPos.x, goalPos.y, goalPos.z);
    }
    else
    {
        ImGui::Text("GoalTiles not found.");
    }
    

    ImGui::Text("GoalFlag: %s", GoalFlag ? "True" : "False");

    ImGui::End();
}