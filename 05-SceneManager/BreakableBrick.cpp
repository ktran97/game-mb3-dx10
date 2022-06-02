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
	piece1 = new BreakableBrickEffect(x, y, -INNIT_VX_BREAKABLE_BRICK_EFFECT, -INNIT_VY_BREAKABLE_BRICK_EFFECT * 2);
	piece2 = new BreakableBrickEffect(x, y, INNIT_VX_BREAKABLE_BRICK_EFFECT, -INNIT_VY_BREAKABLE_BRICK_EFFECT * 2);
	piece3 = new BreakableBrickEffect(x, y, -INNIT_VX_BREAKABLE_BRICK_EFFECT, -INNIT_VY_BREAKABLE_BRICK_EFFECT);
	piece4 = new BreakableBrickEffect(x, y, INNIT_VX_BREAKABLE_BRICK_EFFECT, -INNIT_VY_BREAKABLE_BRICK_EFFECT);
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

	if (!isBreakDown) {
		if (!haveButton)
		{
			if (ButtonP::GetInstance()->isPushed && !InitCoin)
			{
				SetState(BREAKABLE_BRICK_STATE_TRANSFORMS_COIN);
			}
		}
		
		if (state == BREAKABLE_BRICK_STATE_TRANSFORMS_COIN)
		{
			if (GetTickCount64() - ChangeBackToBrickTime >= 5000)
			{
				SetState(COIN_STATE_TRANSFORMS_BRICK);
			}
		}
	}

	if (state == BREAKABLE_BRICK_STATE_BREAK_DOWN)
	{
		DebugOut(L">>> state of breakableBrick is break down (get breakableBrick down effect) >>> \n");
		piece1->Update(dt);
		piece2->Update(dt);
		piece3->Update(dt);
		piece4->Update(dt);
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

	if (state == BREAKABLE_BRICK_STATE_BREAK_DOWN)
	{
		piece1->Render();
		piece2->Render();
		piece3->Render();
		piece4->Render();
	}
	else if (objType == OBJECT_TYPE_COIN)
	{
		aniId = ID_ANI_COIN;
		animations->Get(aniId)->Render(x, y);
	}
	else 
	{
		aniId = ID_ANI_BREAKABLE_BRICK;
		if (buttonCreated)
		{
			aniId = ID_ANI_BREAKABLE_BRICK_IS_UP;
		}
		animations->Get(aniId)->Render(x, y);
	}
	RenderBoundingBox();
}

void BreakableBrick::SetState(int state)
{
	switch (state) {
	case BREAKABLE_BRICK_STATE_TRANSFORMS_COIN:
		objType = OBJECT_TYPE_COIN;
		ChangeBackToBrickTime = GetTickCount64();
		isBlocking = 0;
		InitCoin = true;
		break;

	case BREAKABLE_BRICK_STATE_BREAK_DOWN:
		isBreakDown = true;
		break;

	case BREAKABLE_BRICK_STATE_CREATE_BUTTON:
		buttonCreated = true;
		vy = -BREAKBLE_BRICK_VY;
		ButtonP::GetInstance()->SetPosition(x, y - BRICK_BBOX_HEIGHT);
		ButtonP::GetInstance()->isCreated = true;
		break;

	case COIN_STATE_TRANSFORMS_BRICK:
		objType = OBJECT_TYPE_BREAKABLE_BRICK;
		isBlocking = 1;
		break;

	default:
		break;
	}

	CGameObject::SetState(state);
}

