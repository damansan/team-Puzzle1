#pragma once
#include"System/ModelRenderer.h"
#include"Character.h"

//�{�b�N�X
class Box : public Character
{
public:
	Box() {};
	~Box()override {};

	//�X�V����
	virtual void Update(float elapsedTime) = 0;
	//�`�揈��
	virtual void Render(const RenderContext& rc, ModelRenderer* renderer) = 0;

};