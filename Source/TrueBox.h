#pragma once
#include"System/Model.h"
#include"Box.h"

//�g�D���[�{�b�N�X
class TrueBox : public Box
{
public:
	TrueBox();
	~TrueBox()override;

	//�X�V����
	void Update(float elapsedTime);
	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* renderer)override;

private:
	Model* model = nullptr;

};