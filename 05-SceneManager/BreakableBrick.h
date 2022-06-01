#pragma once
#include "GameObject.h"
#include "Coin.h"
#include "BreakableBrickEffect.h"
#include "debug.h"

#define BRICK_BBOX_WIDTH	16
#define BRICK_BBOX_HEIGHT	16

#define BREAKABLE_BRICK_STATE_TRANSFORMS_COIN	1
#define BREAKABLE_BRICK_STATE_BREAK_DOWN	2
#define BREAKABLE_BRICK_STATE_CREATE_BUTTON	3

#define COIN_STATE_TRANSFORMS_BRICK	4

#define OBJECT_TYPE_BREAKABLE_BRICK	30
#define OBJECT_TYPE_COIN	31

#define ID_ANI_COIN 80005
#define ID_ANI_BREAKABLE_BRICK 10001
#define ID_ANI_BREAKABLE_BRICK_IS_UP	10002

#define INNIT_VX_BREAKABLE_BRICK_EFFECT	0.05
#define INNIT_VY_BREAKABLE_BRICK_EFFECT	0.1

#define BREAKBLE_BRICK_VY	0.05f

class BreakableBrick :
	public CGameObject
{
public:
	int isBlocking;
	int startY;
	bool InitCoin;
	DWORD ChangeBackToBrickTime;
	bool haveButton;
	bool buttonCreated, isBreakDown;

	BreakableBrickEffect* piece1;
	BreakableBrickEffect* piece2;
	BreakableBrickEffect* piece3;
	BreakableBrickEffect* piece4;

	BreakableBrick(float x, float y, bool HaveButton);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetState(int state);


	virtual int IsCollidable()
	{
		return 1;
	};

	virtual int IsBlocking()
	{
		return isBlocking;
	}
};

