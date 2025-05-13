#include"FalseBox.h"

//�R���X�g���N�^
FalseBox::FalseBox()
{
	model = new Model("Data/Model/Slime/Slime.mdl");
	//�X�P�[�����O
	scale.x = scale.y = scale.z = 0.01f;
}

//�f�X�g���N�^
FalseBox::~FalseBox()
{
	delete model;
}

//�X�V����
void FalseBox::Update(float elapsedTime)
{
	//�I�u�W�F�N�g�s��X�V
	UpdateTransform();
	//���f���s��X�V
	model->UpdateTransform();
}

//�`�揈��
void FalseBox::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}

