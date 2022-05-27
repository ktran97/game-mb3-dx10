#pragma once
#include "GameObject.h"
#include "QuestionBrick.h"
#include "Goomba.h"
#include "Koopas.h"

#define TAIL_BBOX_WIDTH 8
#define TAIL_BBOX_HEIGHT 3

class MarioTail :
	public CGameObject
{
public:

	bool IsActive = false;

	ULONGLONG attackTime = 0;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state) {};

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	void OnCollisionWithGoomba(LPGAMEOBJECT& obj);
	void OnCollisionWithQuestionBrick(LPGAMEOBJECT& obj);
	void OnCollisionWithKoopas(LPGAMEOBJECT& obj);
	MarioTail() {};
};

