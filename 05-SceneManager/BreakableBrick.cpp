#include "BreakableBrick.h"

BreakableBrick::BreakableBrick(float x, float y, bool HaveButton) : CGameObject(x, y)
{
	startY = y;
	haveButton = HaveButton;
	objType = OBJECT_TYPE_BREAKABLE_BRICK;
	buttonCreated = false;
	vy = 0;
	InitCoin = isBreakDown = false;
	isBlocking = 1;
}

void BreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if (startY - y >= 5 && vy < 0)
	{
		vy = -vy;
	}

	if (vy > 0 && y >= startY)
	{
		y = startY;
		vy = 0;
	}
}

void BreakableBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (!isBreakDown)
	{
		l = x - BRICK_BBOX_WIDTH / 2;
		t = y - BRICK_BBOX_HEIGHT / 2;
		r = l + BRICK_BBOX_WIDTH;
		b = t + BRICK_BBOX_HEIGHT;
	}
}

void BreakableBrick::Render()
{
	int aniId = -1;
	CAnimations* animations = CAnimations::GetInstance();
	if (objType == OBJECT_TYPE_COIN)
	{
		aniId = ID_ANI_COIN;
		animations->Get(aniId)->Render(x, y);
	}
	else 
	{
		aniId = ID_ANI_BREAKABLE_BRICK;
		animations->Get(aniId)->Render(x, y);
	}
	RenderBoundingBox();
}

void BreakableBrick::SetState(int state)
{
	switch (state) {
	case BREAKABLE_BRICK_STATE_BREAK_DOWN:
		isBreakDown = true;
		break;

	default:
		break;
	}

	CGameObject::SetState(state);
}

