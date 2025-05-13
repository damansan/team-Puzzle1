#include"Stage1.h"

//�R���X�g���N�^
Stage1::Stage1()
{
	model = new Model("Data/Model/Stage/Stage.mdl");
	scale.x = scale.y = scale.z = 0.25f;
}

//�f�X�g���N�^
Stage1::~Stage1()
{
	delete model;
}

//�X�V����
void Stage1::Update(float elapsedTime)
{
	//�I�u�W�F�N�g�s��X�V
	UpdateTransform();
	//���f���s��X�V
	model->UpdateTransform();
}

//�`�揈��
void Stage1::Render(const RenderContext&rc,ModelRenderer*renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}