#include "LastItem.h"

LastItem::LastItem(float x, float y) : CGameObject(x, y)
{
	LastItemType = 0;
	isChosen = false;
	ChangeItemTime = 0;
}

void LastItem::Update(DWORD dt, vector<LPGAMEOBJECT>* obj)
{
	if (!isChosen)
	{
		if (ChangeItemTime == 0)
		{
			ChangeItemTime = GetTickCount64();
		}
		else if (GetTickCount64() - ChangeItemTime >= 100 && GetTickCount64() - ChangeItemTime < 200)
		{
			LastItemType = LAST_ITEM_TYPE_IS_MUSHROOM;
		}
		else if (GetTickCount64() - ChangeItemTime >= 200 && GetTickCount64() - ChangeItemTime < 300)
		{
			LastItemType = LAST_ITEM_TYPE_IS_FLOWER;
		}
		else if (GetTickCount64() - ChangeItemTime >= 300 && GetTickCount64() - ChangeItemTime < 400)
		{
			LastItemType = LAST_ITEM_TYPE_IS_STAR;
			ChangeItemTime = 0;
		}
	}
}

void LastItem::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (isChosen)
	{
		animations->Get(ID_ANI_LAST_ITEM + LastItemType)->Render(x, y - 52);
	}
	else if (!isChosen)
	{
		animations->Get(ID_ANI_LAST_ITEM)->Render(x, y);
	}
}

void LastItem::SetState(int state)
{

}

void LastItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LAST_ITEM_BBOX_SIZE / 2;
	t = y - LAST_ITEM_BBOX_SIZE / 2;
	r = l + LAST_ITEM_BBOX_SIZE;
	b = t + LAST_ITEM_BBOX_SIZE;
}