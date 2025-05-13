#include"GoalTiles.h"

//�R���X�g���N�^
GoalTiles::GoalTiles()
{
	model = new Model("Data/Model/Stage/Stage.mdl");
	scale.x = scale.y = scale.z = 0.25f;
}

//�f�X�g���N�^
GoalTiles::~GoalTiles()
{
	delete model;
}

//�������񂵂��
void GoalTiles::Update(float elapsedTime)
{
	//�I�u�W�F�N�g�s��X�V
	UpdateTransform();
	//���f���s��X�V
	model->UpdateTransform();

}

//�`�揈��
void GoalTiles::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}
