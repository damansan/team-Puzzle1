#pragma once
#include"System/ModelRenderer.h"
#include"Character.h"

class Box : public Character
{
public:
	Box() {};
	~Box()override {};

	virtual void Update(float elapsedTime) = 0;
	virtual void Render(const RenderContext& rc, ModelRenderer* renderer) = 0;

};