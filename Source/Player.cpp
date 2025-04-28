#include "Player.h"
#include "System/Input.h"

Player::Player()
{
	model = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");
	scale.x = scale.y = scale.z = 0.01f;
}

Player::~Player()
{
	delete model;
}

void Player::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();
	float moveSpeed = 5.0f * elapsedTime;
	position.x += ax * moveSpeed;
	position.z += ay * moveSpeed;

	UpdateTransform();

	model->UpdateTransform();
}

// ï`âÊèàóù
void Player::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}

#ifdef _DEBUG
void Player::DrawDebugGUI()
{
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	ImGui::SetNextWindowPos(ImVec2(pos.x + 10, pos.y + 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if(ImGui::Begin("Player",nullptr,ImGuiWindowFlags_None))
	{
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::InputFloat3("Position", &position.x);
			DirectX::XMFLOAT3 a;
			a.x =DirectX::XMConvertToDegrees(angle.x);
			a.y =DirectX::XMConvertToDegrees(angle.y);
			a.z =DirectX::XMConvertToDegrees(angle.z);
			ImGui::InputFloat3("Angle", &a.x);
			angle.x =DirectX::XMConvertToRadians(a.x);
			angle.y =DirectX::XMConvertToRadians(a.y);
			angle.z =DirectX::XMConvertToRadians(a.z);
			// ÉXÉPÅ[Éã
			ImGui::InputFloat3("Scale", &scale.x);
		}
	}
	ImGui::End();
}
#endif // DEBUG
