#include "HUD.h"


HUD::HUD()
{
	speedStack = 0;
	marioIsFlying = false;
}

void HUD::Draw()
{

}

void HUD::setPos(float X, float Y) 
{
	x = X;
	y = Y;
}