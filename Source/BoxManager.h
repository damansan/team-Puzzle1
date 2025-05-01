#pragma once

#include<vector>
#include"Box.h"

//�{�b�N�X�}�l�[�W���[
class BoxManager
{
private:
	BoxManager() {};
	~BoxManager() {};
public:
	//�B��̃C���X�^���X�擾
	static void Generate();
	static BoxManager& Instance()
	{
		static BoxManager instance;
		return instance;
	}
	//�X�V����
	void Update(float elapsedTime);
	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* renderer);
	//�{�b�N�X�S�폜
	void Clear();
	//�{�b�N�X�o�^
	void Register(Box* box);
	void RenderDebugPrimiteve(const RenderContext& rc, ShapeRenderer* renderer);

private:
	std::vector<Box*>boxs;
};