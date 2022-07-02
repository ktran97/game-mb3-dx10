#pragma once
#include "GameObject.h"
#include "AssetIDs.h"

#define ID_ANI_MARIO_IN_WORLD_MAP		100001001

#define MARIO_IN_WORLD_MAP_BBOX_WIDTH	14
#define MARIO_IN_WORLD_MAP_BBOX_HEIGHT	16

class CMarioWM : public CGameObject
{
public:
	CMarioWM(float x, float y) : CGameObject(x, y) {}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void ToLeft();
	void ToTop();
	void ToRight();
	void ToBottom();
};
