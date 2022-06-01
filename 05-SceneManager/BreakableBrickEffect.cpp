#include "BreakableBrickEffect.h"

BreakableBrickEffect::BreakableBrickEffect(float X, float Y, float Vx, float Vy)
{
	x = X;
	y = Y;
	vx = Vx;
	vy = Vy;
}

void BreakableBrickEffect::Update(DWORD dt)
{
	vy += 0.001f * dt;
	x += vx * (float)dt;
	y += vy * (float)dt;
}

void BreakableBrickEffect::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_EFFECT_BREALABLE_BRICK;
	animations->Get(aniId)->Render(x, y);
}

