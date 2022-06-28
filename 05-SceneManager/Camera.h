#pragma once
#include <Windows.h>
#include "Utils.h"
#include "Game.h"

#define SCREEN_WIDTH 266
#define SCREEN_HEIGHT 260
class Camera
{
public:
	float mario_vx, mario_vy = 0, mario_x, mario_y;
	float cam_x, cam_y, cam_vx, cam_vy = 0;

	bool IsFollowingMario;
	bool MarioIsFlying;
	bool MarioIsOnPlatForm;
	bool MarioIsInHiddenMap;

public:
	static Camera* __instance;

	static Camera* GetInstance()
	{
		if (__instance == NULL) __instance = new Camera();
		return __instance;
	}
	Camera();

	void SetCamPos(float x, float y) {
		cam_x = x;
		cam_y = y;
	};

	void GetCamPos(float& x, float& y) {
		x = cam_x;
		y = cam_y;
	}

	float GetCamPosX()
	{
		return cam_x;
	}

	float GetCamPosY()
	{
		return cam_y;
	}
	void SetCamPosX(float x)
	{
		cam_x = x;
	}

	bool IsInCam(float objX, float objY)
	{
		return !(objX < cam_x - 20 || objX - cam_x>SCREEN_WIDTH + 20 || objY < cam_y || objY - cam_y > SCREEN_HEIGHT);
	}

	void Update(DWORD dt);

	void GetMarioAttributes(float vx, float vy, float x, float y, bool isonplatform, bool isflying, bool isInHiddenMap);
};