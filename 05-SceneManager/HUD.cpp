#include "HUD.h"

HUD* HUD::__instance = NULL;

HUD::HUD()
{
	speedStack = 0;
	marioIsFlying = false;
}


void HUD::Draw()
{
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	sprites->Get(ID_SPRITE_HUD)->Draw(Camera::GetInstance()->cam_x + HUD_X, Camera::GetInstance()->cam_y + HUD_Y);
	if (speedStack)
	{
		for (int i = 0; i < speedStack; i++)
		{
			float startX = HUD_START_SPEED_STACK_X + i * 8;
			if (i == 6)
			{
				if (marioIsFlying)
				{
					animations->Get(ID_ANI_SPEEDSTACK_MAX_P)->Render(Camera::GetInstance()->cam_x + startX + 4, Camera::GetInstance()->cam_y + HUD_SPEED_STACK_Y);
				}
				else
				{
					sprites->Get(ID_SPEED_STACK_P)->Draw(Camera::GetInstance()->cam_x + startX + 4, Camera::GetInstance()->cam_y + HUD_SPEED_STACK_Y);
				}
			}
			else
			{
				if (marioIsFlying)
				{
					animations->Get(ID_ANI_SPEEDSTACK_MAX)->Render(Camera::GetInstance()->cam_x + startX, Camera::GetInstance()->cam_y + HUD_SPEED_STACK_Y);
				}
				else
				{
					sprites->Get(ID_SPEED_STACK)->Draw(Camera::GetInstance()->cam_x + startX, Camera::GetInstance()->cam_y + HUD_SPEED_STACK_Y);
				}
			}
		}
	}
}

void HUD::setPos(float xHUD, float yHUD)
{
	x = xHUD;
	y = yHUD;
}