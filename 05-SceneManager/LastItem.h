#pragma once
#include "GameObject.h"

#define LAST_ITEM_BBOX_SIZE			16

#define LAST_ITEM_TYPE_IS_MUSHROOM	1
#define LAST_ITEM_TYPE_IS_FLOWER	2
#define LAST_ITEM_TYPE_IS_STAR		3

#define ID_ANI_LAST_ITEM						99009901

#define ID_ANI_END_WORLD_ITEM_TYPE_IS_MUSHROOM	99009902
#define ID_ANI_END_WORLD_ITEM_TYPE_IS_FLOWER	99009903
#define ID_ANI_END_WORLD_ITEM_TYPE_IS_STAR		99009904


class LastItem : public CGameObject
{
public:
	int LastItemType;
	bool isChosen;

	LastItem(float x, float y);

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* obj = NULL);
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsBlocking()
	{ 
		return 0;
	};
};

