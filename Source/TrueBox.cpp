#include"TrueBox.h"

//�R���X�g���N�^
TrueBox::TrueBox()
{
	model = new Model("Data/Model/Slime/Slime.mdl");
	//�X�P�[�����O
	scale.x = scale.y = scale.z = 0.01f;
}

//�f�X�g���N�^
TrueBox::~TrueBox()
{
	delete model;
}

//�X�V����
void TrueBox::Update(float elapsedTime)
{
	UpdateTransform();
	model->UpdateTransform();
}

//�`�揈��
void TrueBox::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}