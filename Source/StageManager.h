#pragma once
#include<vector>
#include"Stage.h"

class StageManager
{
private:
	StageManager() {};
	~StageManager() {};
public:
	static void Generate();

	//�B��̃C���X�^���X�擾
	static StageManager& Instance()
	{
		static StageManager instance;
		return instance;
	}

	//�X�V����
	void Update(float elapsedTime);
	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* renderer);
	//�X�e�[�W�o�^
	void Register(Stage* stage);
	//�X�e�[�W�S�폜
	void Clear();
	//�X�e�[�W�擾
	Stage* GetStage(int index) { return stages.at(index); }

private:
	std::vector<Stage*>stages;

};