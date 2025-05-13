#include "System/Graphics.h"
#include "SceneGame.h"
#include "Camera.h"
#include "CameraController.h"
#include "StageManager.h"
#include "BoxManager.h"
#include "TrueBox.h"
#include "FalseBox.h"

// ������
void SceneGame::Initialize()
{
	//�X�e�[�W������
	StageManager& stageManager = StageManager::Instance();
	//�X�e�[�W�z�u
	StageManager::Generate();
	//�v���C���[
	player = new Player;
	//�J�����R���g���[���[
	cameraController = new CameraController;
	//�{�b�N�X������
	BoxManager& boxManager = BoxManager::Instance();
	//�{�b�N�X�z�u
	BoxManager::Generate();

	//�J���������ݒ�
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAt(
		DirectX::XMFLOAT3(0, 10, -10), //�n�_
		DirectX::XMFLOAT3(0, 0, 0),    //�����_
		DirectX::XMFLOAT3(0, 1, 0)     //�����
	);
	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(45),//����p
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),//��ʃA�X�y�N�g��
		0.1f,    //�N���b�v����(��)
		1000.0f  //�N���b�v����(��)
	);

	//�W���b�W
	judge = new Judge;

}

// �I����
void SceneGame::Finalize()
{
	//�X�e�[�W
	StageManager::Instance().Clear();
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
	//True�{�b�N�X�S�폜
	BoxManager::Instance().Clear();
	//�W���b�W
	if (judge != nullptr)
	{
		delete judge;
		judge = nullptr;
	}
}

// �X�V����
void SceneGame::Update(float elapsedTime)
{

	//�X�e�[�W�X�V
	StageManager::Instance().Update(elapsedTime);
	//�v���C���[�X�V
	player->Update(elapsedTime);
	//True�{�b�N�X�X�V
	BoxManager::Instance().Update(elapsedTime);
	
	//�J�����R���g���[���[(�v���C���[�̍���������^�[�Q�b�g)
	DirectX::XMFLOAT3 target = player->GetPosition();
	target.y += 0.5f;
	cameraController->SetTarget(target);
	cameraController->Update(elapsedTime);
	
	//�W���b�W�X�V
	judge->GetPosition();
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


	//�J�����p�����[�^�[�ݒ�
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();


	// 3D���f���`��
	{
		//�X�e�[�W
		StageManager::Instance().Render(rc, modelRenderer);
		//�v���C���[
		player->Render(rc, modelRenderer);
		//True�{�b�N�X
		BoxManager::Instance().Render(rc, modelRenderer);
	}

	// 3D�f�o�b�O�`��
	{
#ifdef _DEBUG
		//�v���C���[
		player->RenderDebugPrimiteve(rc, shapeRenderer);
		//True�{�b�N�X
		BoxManager::Instance().RenderDebugPrimiteve(rc, shapeRenderer);

#endif

	}

	// 2D�X�v���C�g�`��
	{

	}
}

// GUI�`��
void SceneGame::DrawGUI()
{
#ifdef _DEBUG
	//�v���C���[�f�o�b�O
	player->DrawGUI();
	//�J�����R���g���[���[
	cameraController->DrawGUI();
	judge->DrawGUI();

#endif 
}

