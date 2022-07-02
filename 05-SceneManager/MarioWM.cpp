#include "MarioWM.h"

void CMarioWM::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	x += vx * dt;
	y += vy * dt;	

	for (int i = 0; i < coObjects->size(); i++)
	{
		if (CCollision::GetInstance()->CheckAABB(this, coObjects->at(i)))
		{
			OnCollisionWithNodeGate(coObjects->at(i), coObjects);
		}
	}
}



void CMarioWM::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_MARIO_IN_WORLD_MAP;
	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
}

void CMarioWM::OnCollisionWithNodeGate(CGameObject* obj, vector<LPGAMEOBJECT>* coObjs)
{

	if (dynamic_cast<CNodeGate*>(obj))
	{
		CNodeGate* nextNode = dynamic_cast<CNodeGate*>(obj);
		if (currentNode == NULL)
		{
			currentNode = nextNode;
		}
		else if (currentNode == nextNode)
		{
			return;
		}
		else if (vx > 0 && x >= (nextNode->x) - 4)
		{
			vx = 0;
			currentNode = nextNode;
		}
		else if (vx < 0 && x <= (nextNode->x) + 2)
		{
			vx = 0;
			currentNode = nextNode;
		}
		else if (vy > 0 && y >= (nextNode->y) - 4)
		{
			vy = 0;
			currentNode = nextNode;
		}
		else if (vy < 0 && y <= (nextNode->y) - 2)
		{
			vy = 0;
			currentNode = nextNode;
		}
	}
}

void CMarioWM::ToLeft()
{
	if (currentNode->allowedToLeft && vx == 0 && vy == 0)
	{
		vx = -0.15f;
	}
}

void CMarioWM::ToTop()
{
	if (currentNode->allowedToTop && vx == 0 && vy == 0)
	{
		vy = -0.15f;
	}
}

void CMarioWM::ToRight()
{
	if (currentNode->allowedToRight && vx == 0 && vy == 0)
	{
		vx = 0.15f;
	}
}

void CMarioWM::ToBottom()
{
	if (currentNode->allowedToBottom && vx == 0 && vy == 0)
	{
		vy = 0.15f;
	}
}

void CMarioWM::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MARIO_IN_WORLD_MAP_BBOX_WIDTH / 2;
	t = y - MARIO_IN_WORLD_MAP_BBOX_HEIGHT / 2;
	r = l + MARIO_IN_WORLD_MAP_BBOX_WIDTH;
	b = t + MARIO_IN_WORLD_MAP_BBOX_HEIGHT;
}

