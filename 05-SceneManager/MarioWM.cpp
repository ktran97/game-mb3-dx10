#include "MarioWM.h"

void CMarioWM::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	x += vx * dt;
	y += vy * dt;
}

void CMarioWM::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_SPRITE_MINI_MARIO;
	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
}

void CMarioWM::ToLeft()
{
}

void CMarioWM::ToTop()
{
}

void CMarioWM::ToRight()
{
}

void CMarioWM::ToBottom()
{
}

void CMarioWM::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MARIO_IN_WORLD_MAP_BBOX_WIDTH / 2;
	t = y - MARIO_IN_WORLD_MAP_BBOX_HEIGHT / 2;
	r = l + MARIO_IN_WORLD_MAP_BBOX_WIDTH;
	b = t + MARIO_IN_WORLD_MAP_BBOX_HEIGHT;
}