#include "Player.h"
#include "System/Input.h"
#include "Camera.h"

//�R���X�g���N�^
Player::Player()
{
	model = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");
	//�X�P�[�����O
	scale.x = scale.y = scale.z = 0.01f;
}

//�f�X�g���N�^
Player::~Player()
{
	delete model;
}

//�X�V����
void Player::Update(float elapsedTime)
{
	////�X�e�B�b�N���͒l����ړ��x�N�g�����擾
	//DirectX::XMFLOAT3 moveVec = GetMoveVec();

	////�ړ�����
	//float moveSpeed = this->moveSpeed * elapsedTime;
	//position.x += moveVec.x * moveSpeed;
	//position.z += moveVec.z * moveSpeed;

	////���X�e�B�b�N�̓��͏������Ƃ�XZ���ʂւ̈ړ�����
	//GamePad& gamePad = Input::Instance().GetGamePad();
	//float ax = gamePad.GetAxisLX();
	//float ay = gamePad.GetAxisLY();
	//float moveSpeed = 5.0f * elapsedTime;
	//position.x += ax * moveSpeed;
	//position.z += ay * moveSpeed;

	//moveCooldown -= elapsedTime;
	//if (moveCooldown < -0.0f)
	//{
	//	InputGridMove();
	//}

	UpdateTransform();
	model->UpdateTransform();

	//�ړ����͏���
	InputMove(elapsedTime);

	//�I�u�W�F�N�g�s��X�V
	UpdateTransform();

	//���f���s��X�V
	model->UpdateTransform();
}

void Player::InputGridMove()
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();

	const float threshold = 0.5f;  // �f�b�h�]�[��
	float step = 1.0f;             // 1�}�X�̋����i�O���b�h�P�ʁj

	if (ax > threshold)
	{
		position.x += step;
		moveCooldown = moveInterval;
	}
	else if (ax < -threshold)
	{
		position.x -= step;
		moveCooldown = moveInterval;
	}
	else if (ay > threshold)
	{
		position.z += step;
		moveCooldown = moveInterval;
	}
	else if (ay < -threshold)
	{
		position.z -= step;
		moveCooldown = moveInterval;
	}
}
//�ړ�����
void Player::Move(float elapsedTime, float vx, float vz, float speed)
{
	speed *= elapsedTime;
	position.x += vx * speed;
	position.z += vz * speed;
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

//�ړ����͏���
void Player::InputMove(float elapsedTime)
{
	//�i�s�x�N�g��
	DirectX::XMFLOAT3 moveVec = GetMoveVec();

	//�ړ�����
	Move(elapsedTime, moveVec.x, moveVec.z, moveSpeed);

	//���񏈗�
	Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);
}


// �`�揈��
void Player::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}



//�f�o�b�OGUI
#ifdef _DEBUG
void Player::DrawDebugGUI()
{
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	ImGui::SetNextWindowPos(ImVec2(pos.x + 10, pos.y + 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Player", nullptr, ImGuiWindowFlags_None))
	{
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::InputFloat3("Position", &position.x);
			DirectX::XMFLOAT3 a;
			a.x = DirectX::XMConvertToDegrees(angle.x);
			a.y = DirectX::XMConvertToDegrees(angle.y);
			a.z = DirectX::XMConvertToDegrees(angle.z);
			ImGui::InputFloat3("Angle", &a.x);
			angle.x = DirectX::XMConvertToRadians(a.x);
			angle.y = DirectX::XMConvertToRadians(a.y);
			angle.z = DirectX::XMConvertToRadians(a.z);
			// �X�P�[��
			ImGui::InputFloat3("Scale", &scale.x);
		}
	}
	ImGui::End();
}
#endif // DEBUG

//�X�e�B�b�N���͒l����ړ��x�N�g�����擾
DirectX::XMFLOAT3 Player::GetMoveVec()const
{
	//���͏����擾
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();

	//�J���������ƃX�e�B�b�N�̓��͒l�ɂ���Đi�s�������v�Z����
	Camera& camera = Camera::Instance();
	const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
	const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

	//�ړ��x�N�g����XZ���ʂɐ����ȃx�N�g���ɂȂ�悤�ɂ���

	//�J�����E�����x�N�g����XZ�P�ʃx�N�g���ɕϊ�
	float cameraRightX = cameraRight.x;
	float cameraRightZ = cameraRight.z;
	float cameraRightLength = sqrt(cameraRightX * cameraRightX + cameraRightZ * cameraRightZ);//���������߂�

	if (cameraRightLength > 0.0f)
	{
		//�P�ʃx�N�g��
		cameraRightX = cameraRightX / cameraRightLength;
		cameraRightZ = cameraRightZ / cameraRightLength;
	}

	//�J�����O�����x�N�g����XZ�P�ʃx�N�g���ɕϊ�
	float cameraFrontX = cameraFront.x;
	float cameraFrontZ = cameraFront.z;
	float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX + cameraFrontZ * cameraFrontZ);

	if (cameraFrontLength > 0.0001f)
	{
		//�P�ʃx�N�g����
		cameraFrontX = cameraFrontX / cameraFrontLength;
		cameraFrontZ = cameraFrontZ / cameraFrontLength;
	}
	else
	{
		//�O�������^��/�^������ɂȂ��Ă��܂��Ă���̂ŁA�f�t�H���g�O�������g��
		cameraFrontX = 0.0f;
		cameraFrontZ = 1.0f;

	}

	// �X�e�B�b�N�̐������͒l���J�����E�����ɔ��f���A
	// �X�e�B�b�N�̐������͒l���J�����O�����ɔ��f���A
	// �i�s�x�N�g�����v�Z����
	DirectX::XMFLOAT3 vec;
	vec.x = (cameraRightX * ax) + (cameraFrontX * ay);
	vec.z = (cameraRightZ * ax) + (cameraFrontZ * ay);
	//Y�������ɂ͈ړ����Ȃ�
	vec.y = 0.0f;

	float len5q = vec.x * vec.x + vec.z * vec.z;
	if (len5q < 0.01f)
	{
		vec.x = vec.z = 0.0f;
	}
	return vec;
}