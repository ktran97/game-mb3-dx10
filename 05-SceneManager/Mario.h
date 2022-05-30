#pragma once
#include "GameObject.h"
#include "QuestionBrick.h"
#include "FirePiranhaPlant.h"
#include "MarioTail.h"
#include "Koopas.h"
#include "Game.h"
#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "ColorBox.h"
#include "Koopas.h"
#include "Collision.h"
#include "Leaf.h"


#include "Animation.h"
#include "Animations.h"
#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_SLOWING_DOWN_X	0.00035f
#define MARIO_ACCEL_RUN_X	0.0007f
#define MARIO_FRICTION		0.006f

#define MARIO_JUMP_SPEED_Y		0.4f
#define MARIO_JUMP_RUN_SPEED_Y	0.45f
#define MARIO_FLYING_SPEED  0.15f

#define MARIO_GRAVITY			0.001f

#define MARIO_JUMP_DEFLECT_SPEED  0.3f
#define MARIO_SLOW_FALLING_SPEED  0.02f

#define MARIO_MAX_SPEED_STACK	7

#define MARIO_SPEEDSTACK_TIME 140
#define MARIO_KICK_KOOPAS_TIME 200
#define MARIO_SLOWFALLING_TIME 300

#define RACOON_ATTACK_TIME 250
#define RACOON_IS_ATTACKED_TIME	600

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_SLOW_FALLING	302
#define MARIO_STATE_SLOW_FALLING_RELEASE	303

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_KICKKOOPAS	700
#define MARIO_STATE_ATTACK	800

#define MARIO_STATE_FLYING	900

#define MARIO_STATE_TRANSFORM_RACOON	901

#define RACOON_STATE_TRANSFORM_MARIO	902

#define MARIO_STATE_RELEASE_KOOPAS	1000

#pragma region ANIMATION_ID
//NORMAL
#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

#define ID_ANI_MARIO_KICKKOOPAS_RIGHT	1701
#define ID_ANI_MARIO_KICKKOOPAS_LEFT	1700

#define ID_ANI_MARIO_HOLDKOOPAS_IDLE_RIGHT	1702
#define ID_ANI_MARIO_HOLDKOOPAS_IDLE_LEFT	1703

#define ID_ANI_MARIO_HOLDKOOPAS_WALK_RIGHT	1704
#define ID_ANI_MARIO_HOLDKOOPAS_WALK_LEFT	1705

#define ID_ANI_MARIO_HOLDKOOPAS_JUMP_RIGHT	1706
#define ID_ANI_MARIO_HOLDKOOPAS_JUMP_LEFT	1707

#define ID_ANI_MARIO_FALLING_RIGHT	1708
#define ID_ANI_MARIO_FALLING_LEFT	1709

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_KICKKOOPAS_RIGHT	1801
#define ID_ANI_MARIO_SMALL_KICKKOOPAS_LEFT	1800

#define ID_ANI_MARIO_SMALL_HOLDKOOPAS_IDLE_RIGHT	1802
#define ID_ANI_MARIO_SMALL_HOLDKOOPAS_IDLE_LEFT		1803

#define ID_ANI_MARIO_SMALL_HOLDKOOPAS_WALK_RIGHT	1804
#define ID_ANI_MARIO_SMALL_HOLDKOOPAS_WALK_LEFT		1805

#define ID_ANI_MARIO_SMALL_HOLDKOOPAS_JUMP_RIGHT	1806
#define ID_ANI_MARIO_SMALL_HOLDKOOPAS_JUMP_LEFT		1807

//RACOON
#define ID_ANI_RACOON_IDLE_RIGHT 1900
#define ID_ANI_RACOON_IDLE_LEFT 1901

#define ID_ANI_RACOON_WALKING_RIGHT 1902
#define ID_ANI_RACOON_WALKING_LEFT 1903

#define ID_ANI_RACOON_JUMP_WALK_RIGHT 1904
#define ID_ANI_RACOON_JUMP_WALK_LEFT 1905

#define ID_ANI_RACOON_FALLING_RIGHT 1906
#define ID_ANI_RACOON_FALLING_LEFT 1907

#define ID_ANI_RACOON_RUNNING_RIGHT 1908
#define ID_ANI_RACOON_RUNNING_LEFT 1909

#define ID_ANI_RACOON_FLYING_RIGHT 1910
#define ID_ANI_RACOON_FLYING_LEFT 1911

#define ID_ANI_RACOON_SITTING_RIGHT 1912
#define ID_ANI_RACOON_SITTING_LEFT 1913

#define ID_ANI_RACOON_BRACE_RIGHT 1914
#define ID_ANI_RACOON_BRACE_LEFT 1915

#define ID_ANI_RACOON_SLOWFALLING_RIGHT	1916
#define ID_ANI_RACOON_SLOWFALLING_LEFT	1917

#define ID_ANI_RACOON_ATTACK_RIGHT	1918
#define ID_ANI_RACOON_ATTACK_LEFT	1919

#define ID_ANI_RACOON_FALLING_FLYING_RIGHT 1920
#define ID_ANI_RACOON_FALLING_FLYING_LEFT 1921

#define ID_ANI_RACOON_EFFECT_WHEN_ATTACKED	1922

#define ID_ANI_RACOON_KICKKOOPAS_RIGHT	1923
#define ID_ANI_RACOON_KICKKOOPAS_LEFT	1924

#define ID_ANI_RACOON_HOLDKOOPAS_IDLE_RIGHT	1925
#define ID_ANI_RACOON_HOLDKOOPAS_IDLE_LEFT	1926

#define ID_ANI_RACOON_HOLDKOOPAS_WALK_RIGHT	1927
#define ID_ANI_RACOON_HOLDKOOPAS_WALK_LEFT	1928

#define ID_ANI_RACOON_HOLDKOOPAS_JUMP_RIGHT	1929
#define ID_ANI_RACOON_HOLDKOOPAS_JUMP_LEFT	1930

#pragma endregion

#define GROUND_Y 160.0f

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACOON	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500

class CMario : public CGameObject
{
	BOOLEAN isSitting, isOnPlatform;

	float maxVx;
	float ax; // acceleration on x 
	float ay; // acceleration on y

	bool IsSlowFalling;
	DWORD SlowFallingTime;

	bool IsFalling;
	DWORD FallingTime;

	DWORD FlyingTime;

	bool IsAttack;
	DWORD AttackTime;

	bool IsKickKoopas;
	DWORD KickKoopasTime;

	bool isHoldingKoopas;
	DWORD effectTime;

	int speedStack;
	int level;
	int coin;

	MarioTail* tail;
	Koopas* koopasHold;
	
	DWORD SpeedStackTime;


	ULONGLONG untouchable_start;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithItem(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();

public:
	int untouchable;
	bool isFlying;

	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;
		isFlying = IsAttack = IsKickKoopas = false;
		/*level = MARIO_LEVEL_SMALL;*/
		level = MARIO_LEVEL_RACOON;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		speedStack = 0;
		AttackTime = SpeedStackTime = 0;
		tail = new MarioTail();
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt);

	void SetLevel(int l);
	void IncreaseSpeedStack();
	void DecreaseSpeedStack();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void HandleMarioIsAttacked();
	void HandleMarioIsFlying(DWORD dt);
	void HandleMarioTransformRacoon();
	void HandleMarioSlowFalling();
	void HandleMarioUntouchable();
	void HandleMarioKickKoopas();
	void HandleRacoonAttack(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void HandleMarioHoldingKoopas();
	void HandleMarioStateIdle();
	void HandleMarioRunning();

	bool CheckMarioIsOnPlatform()
	{
		return isOnPlatform;
	};

	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	int IsBlocking()
	{
		return (state != MARIO_STATE_DIE && untouchable == 0);
	}

	int GetMarioLevel()
	{
		return level;
	}

	int GetSpeedStack()
	{
		return speedStack;
	}

	void StartUntouchable()
	{
		untouchable = 1;
		untouchable_start = GetTickCount64();
	}

	bool CheckIsFlying()
	{
		return isFlying;
	}

	bool CheckMarioHoldKoopas() {
		return isHoldingKoopas;
	}

};
