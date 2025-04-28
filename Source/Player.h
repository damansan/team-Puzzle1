#pragma once

#include "System/ModelRenderer.h"
#include "Character.h"

class Player : public Character
{
public:
	Player();
	~Player() override;

	void Update(float elapsedTime);
	void Render(const RenderContext& rc, ModelRenderer* renderer);

#ifdef _DEBUG
	void DrawDebugGUI();

#endif


private:
	Model* model = nullptr;
};
