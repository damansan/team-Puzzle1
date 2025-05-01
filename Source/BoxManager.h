#pragma once

#include<vector>
#include"Box.h"

class BoxManager
{
private:
	BoxManager() {};
	~BoxManager() {};
public:
	static void Generate(int Counter);
	static BoxManager& Instance()
	{
		static BoxManager instance;
		return instance;
	}
	void Update(float elapsedTime);
	void Render(const RenderContext& rc, ModelRenderer* renderer);
	void Clear();
	void Register(Box* box);
	void RenderDebugPrimiteve(const RenderContext& rc, ShapeRenderer* renderer);

private:
	std::vector<Box*>boxs;
};