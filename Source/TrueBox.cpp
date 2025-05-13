#include"TrueBox.h"

//�R���X�g���N�^
TrueBox::TrueBox()
{
	model = new Model("Data/Model/Moai/moai01.mdl");
	//�X�P�[�����O
	scale.x = scale.y = scale.z = 0.1f;
}

//�f�X�g���N�^
TrueBox::~TrueBox()
{
	delete model;
}

//�X�V����
void TrueBox::Update(float elapsedTime)
{
	//�I�u�W�F�N�g�s��X�V
	UpdateTransform();
	//���f���s��X�V
	model->UpdateTransform();
}

//�`�揈��
void TrueBox::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}

