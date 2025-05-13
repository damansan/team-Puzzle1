#pragma once

#include<set>
#include<vector>
#include"Box.h"

//�{�b�N�X�}�l�[�W���[
class BoxManager
{
private:
	BoxManager() {};
	~BoxManager() {};
public:
	static void Generate();
	
	//�B��̃C���X�^���X�擾
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
	//�f�o�b�O�v���~�e�B�u�`��
	void RenderDebugPrimiteve(const RenderContext& rc, ShapeRenderer* renderer);
	//�{�b�N�X���擾
	int GetBoxCount()const { return static_cast<int>(boxs.size()); }
	//�{�b�N�X�擾
	Box* GetBox(int index) { return boxs.at(index); }

private:
	std::vector<Box*>boxs;
};