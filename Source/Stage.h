#pragma once
#include"System/ModelRenderer.h"
#include"Character.h"

// �X�e�[�W
class Stage:public Character
{
public:
	Stage() {};
	//~Stage()override {};
	virtual ~Stage() {};
	//�X�V����
	virtual void Update(float elapsedTime) = 0;
	//�`�揈��
	virtual void Render(const RenderContext& rc, ModelRenderer* renderer) = 0;

};