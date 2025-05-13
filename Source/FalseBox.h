#pragma once
#include"System/Model.h"
#include"Box.h"

//False�{�b�N�X
class FalseBox : public Box
{
public:
	FalseBox();
	~FalseBox()override;

	//�X�V����
	void Update(float elapsedTime)override;
	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* renderer)override;
private:
	Model* model = nullptr;

};