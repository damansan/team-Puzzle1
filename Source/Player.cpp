#include "Player.h"
#include "System/Input.h"
#include "BoxManager.h"
#include "Collision.h"
#include "FalseBox.h"
#include "Camera.h"

//�R���X�g���N�^
Player::Player()
{
	//model = new Model("Data/Model/Player/Player.mdl");
	model = new Model("Data/Model/Ufo/ufo.mdl");
	//�X�P�[�����O
	scale.x = scale.y = scale.z = 0.5f;
	position.z = -5;
	position.y = 0.01f;
}

//�f�X�g���N�^
Player::~Player()
{
	delete model;
}

//�X�V����
void Player::Update(float elapsedTime)
{

	//�ړ����͏���
	InputMove(elapsedTime);

	//�v���C���[�ƃ{�b�N�X�̏Փ˔���
	CollisionPlayerVsBoxs();

	//�I�u�W�F�N�g�s��X�V
	UpdateTransform();

	//���f���s��X�V
	model->UpdateTransform();

}

//�`�揈��
void Player::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}

//�ړ�����
void Player::Move(float elapsedTime, float vx, float vz, float speed)
{
	speed *= elapsedTime;
	position.x += vx * speed;
	position.z += vz * speed;
}
//�ړ����͏���
void Player::InputMove(float elapsedTime)
{
	//�i�s�x�N�g���擾
	DirectX::XMFLOAT3 moveVec = GetMoveVec();
	//�ړ�����
	Move(elapsedTime, moveVec.x, moveVec.z, moveSpeed);
	//���񏈗�
	Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);
}
//���񏈗�
void Player::Turn(float elapsedTime, float vx, float vz, float speed)
{
	speed *= elapsedTime;

	//�i�s�x�N�g�����[���x�N�g���̏ꍇ�͏�������K�v�Ȃ�
	float length = sqrtf(vx * vx + vz * vz);
	if (length < 0.001f) return;

	//�i�s�x�N�g����P�ʃx�N�g����
	vx /= length;
	vz /= length;

	//���g�̉�]����O���������߂�
	float frontX = sinf(angle.y);
	float frontZ = cosf(angle.y);

	//��]�p�����߂邽�߁A�Q�̃x�N�g���̓��ς��v�Z����
	float dot = (frontX * vx) + (frontZ * vz);

	//���ϒl��-1.0�`1.0�ŕ\������Ă���A�Q�̒P�ʃx�N�g���̊p�x��
	// �������ق�1.0�ɋ߂Â��Ƃ��������𗘗p���ĉ�]���x�𒲐�����
	float rot = 1.0 - dot;
	if (rot > speed) rot = speed;

	//���E������s�����߂ɂQ�̒P�ʃx�N�g���̊O�ς��v�Z����
	float cross = (frontZ * vx) - (frontX * vz);

	//2D�̊O�ϒl�����̏ꍇ�����̏ꍇ�ɂ���č��E���肪�s����
	//���E������s�����Ƃɂ���č��E��]��I������
	if (cross < 0.0f)
	{
		angle.y -= rot;
	}
	else
	{
		angle.y += rot;
	}

}

//�X�e�B�b�N���͒l����ړ��x�N�g�����擾
DirectX::XMFLOAT3 Player::GetMoveVec()const
{
	//GamePad& gamePad = Input::Instance().GetGamePad();
	//const GamePadButton ButtonW = GamePad::BTN_1;
	//const GamePadButton ButtonA = GamePad::BTN_2;
	//const GamePadButton ButtonS = GamePad::BTN_3;
	//const GamePadButton ButtonD = GamePad::BTN_4;

	//���͏����擾
	//float ax =0.0f;
	//float ay =0.0f;

	//if (gamePad.GetButtonDown() & ButtonW)ay += 10.0f;
	//if (gamePad.GetButtonDown() & ButtonS)ay -= 10.0f;
	//if (gamePad.GetButtonDown() & ButtonD)ax += 10.0f;
	//if (gamePad.GetButtonDown() & ButtonA)ax -= 10.0f;


	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();


	//�J���������ƃX�e�B�b�N���͒l�ɂ���Đi�s�������v�Z����
	Camera& camera = Camera::Instance();
	const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
	const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

	//�ړ��x�N�g����XZ���ʂɐ����ȃx�N�g���ɂȂ�悤�ɂ���

	//�J�����E�����x�N�g����XZ�P�ʃx�N�g���ɕϊ�
	float cameraRightX = cameraRight.x;
	float cameraRightZ = cameraRight.z;
	float cameraRightLenght = sqrtf(cameraRightX * cameraRightX + cameraRightZ * cameraRightZ);
	if (cameraRightLenght > 0.0f)
	{
		//�P�ʃx�N�g����
		cameraRightX /= cameraRightLenght;
		cameraRightZ /= cameraRightLenght;
	}
	//�J�����O�����x�N�g����ZX�P�ʃx�N�g���ɕϊ�
	float cameraFrontX = cameraFront.x;
	float cameraFrontZ = cameraFront.z;
	float cameraFrontLenght = sqrtf(cameraFrontX * cameraFrontX + cameraFrontZ * cameraFrontZ);
	if (cameraFrontLenght > 0.0f)
	{
		//�P�ʃx�N�g����
		cameraFrontX /= cameraFrontLenght;
		cameraFrontZ /= cameraFrontLenght;
	}

	//�X�e�B�b�N�̐������͒l���J�����E�����ɔ��f���A
	//�X�e�B�b�N�̐������͒l���J�����O�����ɔ��f���A
	//�i�s�x�N�g�����v�Z
	DirectX::XMFLOAT3 vec;
	vec.x = (cameraRightX * ax) + (cameraFrontX * ay);
	vec.z = (cameraRightZ * ax) + (cameraFrontZ * ay);
	// Y�������ɂ͈ړ����Ȃ�
	vec.y = 0.0f;
	return vec;
}

//�v���C���[�ƃ{�b�N�X�̓����蔻��
void Player::CollisionPlayerVsBoxs()
{
	BoxManager& boxManager = BoxManager::Instance();

	// ��������Ń{�b�N�X�Ƃ̏Փˏ���
	int boxCount = boxManager.GetBoxCount();
	for (int i = 0; i < boxCount; ++i)
	{
		Box* box = boxManager.GetBox(i);

		// FalseBox �ȊO�Ƃ����Փˏ������s��
		if (dynamic_cast<FalseBox*>(box) == nullptr)
		{
			DirectX::XMFLOAT3 outPosition;

			// �Փˏ����i�l�p vs �l�p�j
			if (Collision::IntersectAndPushBoxVSBox(
				this->position,
				this->halfSize,  // �v���C���[�̔��T�C�Y
				box->GetPosition(),
				box->GethalfSize(),  // �{�b�N�X�̔��T�C�Y
				outPosition))
			{
				// �����o����̈ʒu�ݒ�
				box->SetPosition(outPosition);
			}
		}
	}
}
//�f�o�b�O�pGUI�`��
#ifdef _DEBUG
void Player::DrawGUI()
{
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	ImGui::SetNextWindowPos(ImVec2(pos.x + 10, pos.y + 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if(ImGui::Begin("Player",nullptr,ImGuiWindowFlags_None))
	{
		//�g�����X�t�H�[��
		if (ImGui::CollapsingHeader("Player Position", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//�ʒu
			ImGui::InputFloat3("Position", &position.x);
			//��]
			DirectX::XMFLOAT3 a;
			a.x =DirectX::XMConvertToDegrees(angle.x);
			a.y =DirectX::XMConvertToDegrees(angle.y);
			a.z =DirectX::XMConvertToDegrees(angle.z);
			ImGui::InputFloat3("Angle", &a.x);
			angle.x =DirectX::XMConvertToRadians(a.x);
			angle.y =DirectX::XMConvertToRadians(a.y);
			angle.z =DirectX::XMConvertToRadians(a.z);
			 //�X�P�[��
			ImGui::InputFloat3("Scale", &scale.x);

		}
		//�W���b�W
		//if (ImGui::CollapsingHeader("TrueBoX & GoalTile Position & GoalFlag", ImGuiTreeNodeFlags_DefaultOpen))
		//{
		//	judge.DrawGUI();
		//}

	}
	ImGui::End();
}
#endif // DEBUG
