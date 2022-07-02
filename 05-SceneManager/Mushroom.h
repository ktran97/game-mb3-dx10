#pragma once
#include "debug.h"
#include "GameObject.h"

#define MUSHROOM_WIDTH 16
#define MUSHROOM_HEIGHT 16
#define MUSHROOM_GRAVITY    0.001f

#define MUSHROOM_INNIT_SPEED    0.06f
#define MUSHROOM_SPEED          0.05f

#define MUSHROOM_STATE_BEING_INNITED   1
#define MUSHROOM_STATE_INNITED   2

#define ID_ANI_MUSHROOM 80000

class Mushroom :
    public CGameObject
{
protected:
    bool isInnited;
    float startY;
    int ItemType;
public:
    Mushroom(float x, float y) :CGameObject(x, y) {
        isInnited = false;
        startY = y;
        ItemType = 1;
        isitem = true;
    }
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt);
    void Render();
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    void SetState(int state);
    int IsBlocking() {
    	return 0;
    }
    int IsCollidable() {
        return 1;
    }
};