#pragma once
#include "GameObject.h"
#include "FireBullet.h"

#define FIRE_PIRANHAPLANT_UP_HEIGHT		16
#define FIRE_PIRANHAPLANT_ATTACK_ZONE	100

#define FIRE_PIRANHAPLANT_BBOX_WIDTH	16
#define FIRE_PIRANHAPLANT_BBOX_HEIGHT	34

#define GREEN_FIRE_PLANT_BBOX_HEIGHT	26

#define MAX_ATTACK_ZONE	150
#define MIN_ATTACK_ZONE	100

#define FIRE_PIRANHAPLANT_STATE_UP		1
#define FIRE_PIRANHAPLANT_STATE_DOWN	2

#define ID_ANI_FIRE_PLANT_LEFT_DOWN		210000
#define ID_ANI_FIRE_PLANT_RIGHT_DOWN	210001
#define ID_ANI_FIRE_PLANT_LEFT_UP		210002
#define ID_ANI_FIRE_PLANT_RIGHT_UP		210003

#define ID_ANI_FIRE_PLANT_ATTACK_LEFT_DOWN	210004
#define ID_ANI_FIRE_PLANT_ATTACK_RIGHT_DOWN	210005
#define ID_ANI_FIRE_PLANT_ATTACK_LEFT_UP	210006
#define ID_ANI_FIRE_PLANT_ATTACK_RIGHT_UP	210007

#define ID_ANI_GREEN_FIRE_PLANT_LEFT_DOWN	220000
#define ID_ANI_GREEN_FIRE_PLANT_RIGHT_DOWN	220001
#define ID_ANI_GREEN_FIRE_PLANT_LEFT_UP		220002
#define ID_ANI_GREEN_FIRE_PLANT_RIGHT_UP	220003

#define ID_ANI_GREEN_FIRE_PLANT_ATTACK_LEFT_DOWN	220004
#define ID_ANI_GREEN_FIRE_PLANT_ATTACK_RIGHT_DOWN	220005
#define ID_ANI_GREEN_FIRE_PLANT_ATTACK_LEFT_UP		220006
#define ID_ANI_GREEN_FIRE_PLANT_ATTACK_RIGHT_UP		220007

#define FIRE_PLANT			1
#define GREEN_FIRE_PLANT	2

class FirePiranhaPlant :
	public CGameObject
{
public:
	float ax;
	float ay;
	int aniId;

	int plantType;

	float minY, maxY;

	bool isAttack;
	FireBullet* fireBullet;
	float enemyX, enemyY;
	DWORD CalcAtkTime;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; };

	void CalcAttackEnemy();
	void CreateFireBullet();

	void GetAniFirePlant();
	void GetAniGreenFirePlant();
public:
	void GetEnemyPos(float EnemyX, float EnemyY) {
		enemyX = EnemyX;
		enemyY = EnemyY;
	}
	FirePiranhaPlant(float x, float y, int type) :CGameObject(x, y) {
		if (type == FIRE_PLANT)
		{
			minY = y - FIRE_PIRANHAPLANT_UP_HEIGHT * 2 - FIRE_PIRANHAPLANT_UP_HEIGHT / 2;
			maxY = y + FIRE_PIRANHAPLANT_UP_HEIGHT - FIRE_PIRANHAPLANT_UP_HEIGHT / 2;
		}
		else
		{
			minY = y - FIRE_PIRANHAPLANT_UP_HEIGHT * 2 - FIRE_PIRANHAPLANT_UP_HEIGHT / 4;
			maxY = y + FIRE_PIRANHAPLANT_UP_HEIGHT - FIRE_PIRANHAPLANT_UP_HEIGHT / 2;
		}
		SetState(FIRE_PIRANHAPLANT_STATE_UP);
		fireBullet = new FireBullet(x, y);
		enemyX = enemyY = 0;
		plantType = type;
	};
	virtual void SetState(int state);
};

