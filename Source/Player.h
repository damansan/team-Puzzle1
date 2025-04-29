#pragma once

#include "System/ModelRenderer.h"
#include "Character.h"

//�v���C���[
class Player : public Character
{
public:
	Player();
	~Player() override;

	//�X�V����
	void Update(float elapsedTime);
	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* renderer);

#ifdef _DEBUG
	void DrawDebugGUI();

#endif


private:
	Model* model = nullptr;
};
