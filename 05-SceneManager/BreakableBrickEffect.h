#pragma once
#include "GameObject.h"
#define ID_ANI_EFFECT_BREALABLE_BRICK	10003
class BreakableBrickEffect
{
protected:
	float x, y, vx, vy;
public:

	BreakableBrickEffect(float X, float Y, float Vx, float Vy);
	
	void Update(DWORD dt);
	void Render();
};