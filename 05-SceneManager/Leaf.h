#pragma once
#include "GameObject.h"
#define LEAF_GRAVITY 0.0006f

#define LEAF_WIDTH  16
#define LEAF_HEIGHT  14

#define LEAF_INNIT_SPEED    0.1f

#define LEAF_STATE_INNIT 1
#define LEAF_STATE_FALLING 2

#define ID_ANI_LEAF_FALLING_RIGHT
#define ID_ANI_LEAF_FALLING_RIGHT   80001
#define ID_ANI_LEAF_FALLING_LEFT   80002

class Leaf :public CGameObject
{
protected:
	bool isInnited;
	float startY;
	int ItemType;
	DWORD MovingTime;
public:
	Leaf(float x, float y);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;

	void Render() override;
	void SetState(int state) override;
	void LeafMoving();

	int isBlocking()
	{
		return 0;
	}

	int isConllidable()
	{
		return 1;
	}
};

