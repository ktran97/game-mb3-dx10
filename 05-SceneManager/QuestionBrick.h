#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Mushroom.h"
#include "Coin.h"

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define QUESTION_BRICK_UP 5

#define QUESTION_BRICK_STATE_START_INNIT 2
#define QUESTION_BRICK_STATE_INNITED 3

#define ID_ANI_QUESTION_BRICK_HAVEITEM	70000
#define ID_ANI_QUESTION_BRICK_HAVENOITEM	70001

#define QUESTION_BRICK_VY	0.03f
#define COIN_UP_VY	0.1f

class QuestionBrick : public CGameObject {
public:
	int startY;
	bool readyInnitItem;
	bool innitItemSuccess;
	int Item;
	CCoin* coin;
	bool InitCoin;
	DWORD coinUpTime;

	QuestionBrick(float x, float y, int item);

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};
