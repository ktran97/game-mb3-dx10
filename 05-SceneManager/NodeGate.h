#pragma once
#include "GameObject.h"

#define WORLD_STATION_BBOX_WIDTH	8
#define WORLD_STATION_BBOX_HEIGHT	8

class CNodeGate : public CGameObject
{
	int sceneId;
public:
	bool allowedToLeft, allowedToTop, allowedToRight, allowedBottom;

	CNodeGate(int id, bool left, bool top, bool right, bool bottom);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
