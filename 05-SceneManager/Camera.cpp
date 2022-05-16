#include "Camera.h"


Camera* Camera::__instance = NULL;
Camera::Camera()
{
	cam_y = 240;
	cam_vy = 0.0;
}

void Camera::Update(DWORD dt)
{
	/*if (AutoMove < 1)
	{
		if (IsFollowingMario)
		{
			SetCamSpeed();
			cam_y += cam_vy * dt;
		}
		else
			cam_vy = 0;
		floor(cam_y);
	}
	else
	{
		cam_vy = 0;
		cam_x += cam_vx * dt;
	}*/
	cam_y += cam_vy * dt;
}

void Camera::SetCamSpeed()

{
	if (Mariovy < 0 && cam_y >= 0)
		cam_vy = Mariovy;
	else {
		if (cam_y <= 0)
			cam_y = 0;
		cam_vy = Mariovy * 0.5;
	}
	if (cam_vy > 0)
	{
		if (cam_y >= 240)
		{
			IsFollowingMario = false;
			cam_vy = 0;
			cam_y = 240;
		}
	}
}