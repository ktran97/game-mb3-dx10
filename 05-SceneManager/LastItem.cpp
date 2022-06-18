#include "LastItem.h"

LastItem::LastItem(float x, float y) : CGameObject(x, y)
{
	LastItemType = 0;
	isChosen = false;
}

void LastItem::Update(DWORD dt, vector<LPGAMEOBJECT>* obj)
{

}

void LastItem::Render()
{
	int aniId = ID_ANI_LAST_ITEM;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
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