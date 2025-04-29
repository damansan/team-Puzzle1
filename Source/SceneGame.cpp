#include "System/Graphics.h"
#include "SceneGame.h"
#include "Camera.h"

// ������
void SceneGame::Initialize()
{
	//�X�e�[�W
	stage = new Stage;
	//�v���C���[
	player = new Player;
	//�J�����R���g���[���[
	cameraController = new  CameraController;

	//�J�����̏����ݒ�
	Graphics& graphice = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAt(
		DirectX::XMFLOAT3(0, 10, -10), //���_
		DirectX::XMFLOAT3(0, 0, 0),    //���ӓ_
		DirectX::XMFLOAT3(0, 1, 0)     //�����
	);

	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(45),
		graphice.GetScreenWidth()/graphice.GetScreenHeight(),
		0.1f,
		1000.0f
	);



}

// �I����
void SceneGame::Finalize()
{
	//�X�e�[�W
	if (stage != nullptr)
	{
		delete stage;
		stage = nullptr;
	}
	//�v���C���[
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	//�J�����R���g���[���[
	if (cameraController != nullptr)
	{
		delete cameraController;
		cameraController = nullptr;
	}
}

// �X�V����
void SceneGame::Update(float elapsedTime)
{
	//�X�e�[�W
	stage->Update(elapsedTime);
	//�v���C���[
	player->Update(elapsedTime);

	//�J�����R���g���[���[�̍X�V����
	DirectX::XMFLOAT3 target = player->GetPosition();
	target.y += 0.5f;
	cameraController->SeTarget(target);
	cameraController->Update(elapsedTime);
}

// �`�揈��
void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ShapeRenderer* shapeRenderer = graphics.GetShapeRenderer();
	ModelRenderer* modelRenderer = graphics.GetModelRenderer();

	// �`�揀��
	RenderContext rc;
	rc.deviceContext = dc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f };	// ���C�g�����i�������j
	rc.renderState = graphics.GetRenderState();

	//�J�����p�����[�^�ݒ�
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();

	//// �r���[�s��
	//{
	//	DirectX::XMFLOAT3 eye = { 0, 10, -10 };	// �J�����̎��_�i�ʒu�j
	//	DirectX::XMFLOAT3 focus = { 0, 0, 0 };	// �J�����̒����_�i�^�[�Q�b�g�j
	//	DirectX::XMFLOAT3 up = { 0, 1, 0 };		// �J�����̏����

	//	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&eye);
	//	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	//	DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);
	//	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
	//	DirectX::XMStoreFloat4x4(&rc.view, View);
	//}
	//// �v���W�F�N�V�����s��
	//{
	//	float fovY = DirectX::XMConvertToRadians(45);	// ����p
	//	float aspectRatio = graphics.GetScreenWidth() / graphics.GetScreenHeight();	// ��ʏc���䗦
	//	float nearZ = 0.1f;	// �J�������f���o���̍ŋߋ���
	//	float farZ = 1000.0f;	// �J�������f���o���̍ŉ�����
	//	DirectX::XMMATRIX Projection = DirectX::XMMatrixPerspectiveFovLH(fovY, aspectRatio, nearZ, farZ);
	//	DirectX::XMStoreFloat4x4(&rc.projection, Projection);
	//}

	// 3D���f���`��
	{
		//�X�e�[�W
		stage->Render(rc, modelRenderer);
		//�v���C���[
		player->Render(rc, modelRenderer);
	}

	// 3D�f�o�b�O�`��
	{

	}

	// 2D�X�v���C�g�`��
	{

	}
}

// GUI�`��
void SceneGame::DrawGUI()
{
#ifdef _DEBUG//�f�o�b�O�̎��̂ݒʂ�
	player->DrawDebugGUI();
#endif 

}
