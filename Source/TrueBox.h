#pragma once
#include"System/Model.h"
#include"Box.h"

//True�{�b�N�X
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