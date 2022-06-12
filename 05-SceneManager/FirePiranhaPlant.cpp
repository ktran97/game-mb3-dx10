#include "FirePiranhaPlant.h"
#include "debug.h"

void FirePiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (plantType == FIRE_PLANT)
	{
		top = y - FIRE_PIRANHAPLANT_UP_HEIGHT / 2;
		bottom = top + FIRE_PIRANHAPLANT_BBOX_HEIGHT;
	}
	else {
		top = y - GREEN_FIRE_PLANT_BBOX_HEIGHT / 2;
		bottom = top + GREEN_FIRE_PLANT_BBOX_HEIGHT;
	}
	left = x - FIRE_PIRANHAPLANT_BBOX_WIDTH / 2;
	right = left + FIRE_PIRANHAPLANT_BBOX_WIDTH;
}

void FirePiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	if (vy < 0) {
		if (y <= minY) {
			vy = 0;
			y = minY;
		}
	}
	else if (vy > 0) {
		if (y >= maxY) {
			vy = 0;
			y = maxY;
		}
	}
	if (y == minY) {
		CalcAttackEnemy();
	}
	if (state == FIRE_PIRANHAPLANT_STATE_UP) {
		if (GetTickCount64() - CalcAtkTime >= 3000) {
			SetState(FIRE_PIRANHAPLANT_STATE_DOWN);
		}
	}
	else {
		if (GetTickCount64() - CalcAtkTime >= 2000) {
			SetState(FIRE_PIRANHAPLANT_STATE_UP);
		}
	}

	if (fireBullet->isActivate)
		fireBullet->Update(dt, coObjects);
}

void FirePiranhaPlant::Render()
{
	aniId = -1;
	if (plantType == FIRE_PLANT)
	{
		GetAniFirePlant();
	}
	else
	{
		GetAniGreenFirePlant();
	}

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	if (fireBullet->isActivate)
	{
		fireBullet->Render();
		/*DebugOut(L"helloBullet\n");*/
	}
}

void FirePiranhaPlant::GetAniFirePlant()
{
	if (x > enemyX) {
		if (y == minY) {
			if (enemyY < minY)aniId = ID_ANI_FIRE_PLANT_ATTACK_LEFT_UP;
			else aniId = ID_ANI_FIRE_PLANT_ATTACK_LEFT_DOWN;
		}
		else if (enemyY < minY)aniId = ID_ANI_FIRE_PLANT_LEFT_UP;
		else aniId = ID_ANI_FIRE_PLANT_LEFT_DOWN;
	}
	else {
		if (y == minY) {
			if (enemyY < minY)aniId = ID_ANI_FIRE_PLANT_ATTACK_RIGHT_UP;
			else aniId = ID_ANI_FIRE_PLANT_ATTACK_RIGHT_DOWN;
		}
		else if (enemyY < minY)aniId = ID_ANI_FIRE_PLANT_RIGHT_UP;
		else aniId = ID_ANI_FIRE_PLANT_RIGHT_DOWN;
	}

	if (aniId == -1) aniId = ID_ANI_FIRE_PLANT_LEFT_DOWN;
}

void FirePiranhaPlant::GetAniGreenFirePlant()
{
	if (x > enemyX) {
		if (y == minY) {
			if (enemyY < minY)aniId = ID_ANI_GREEN_FIRE_PLANT_ATTACK_LEFT_UP;
			else aniId = ID_ANI_GREEN_FIRE_PLANT_ATTACK_LEFT_DOWN;
		}
		else if (enemyY < minY)aniId = ID_ANI_GREEN_FIRE_PLANT_LEFT_UP;
		else aniId = ID_ANI_GREEN_FIRE_PLANT_LEFT_DOWN;
	}
	else {
		if (y == minY) {
			if (enemyY < minY)aniId = ID_ANI_GREEN_FIRE_PLANT_ATTACK_RIGHT_UP;
			else aniId = ID_ANI_GREEN_FIRE_PLANT_ATTACK_RIGHT_DOWN;
		}
		else if (enemyY < minY)aniId = ID_ANI_GREEN_FIRE_PLANT_RIGHT_UP;
		else aniId = ID_ANI_GREEN_FIRE_PLANT_RIGHT_DOWN;
	}

	if (aniId == -1) aniId = ID_ANI_GREEN_FIRE_PLANT_LEFT_DOWN;
}

void FirePiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIRE_PIRANHAPLANT_STATE_UP:
		vy = -0.05;
		CalcAtkTime = GetTickCount64();
		break;
	case FIRE_PIRANHAPLANT_STATE_DOWN:
		vy = 0.05;
		CalcAtkTime = GetTickCount64();
		break;
	default:
		break;
	}
}

void FirePiranhaPlant::CalcAttackEnemy()
{
	if (abs(x - enemyX) <= MAX_ATTACK_ZONE && abs(y - enemyY) <= MAX_ATTACK_ZONE)
	{
		CreateFireBullet();
	}
}

void FirePiranhaPlant::CreateFireBullet()
{
	float VxBullet, VyBullet, BulletX, BulletY;
	if (abs(x - enemyX) <= MIN_ATTACK_ZONE)
	{
		if (enemyY < y)
			VyBullet = -0.05;
		else
			VyBullet = 0.05;
	}
	else
	{
		if (enemyY < y)
			VyBullet = -0.03;
		else
			VyBullet = 0.03;
	}
	if (enemyX > x)
	{
		VxBullet = 0.05;
		nx = 1;
		BulletX = x + FIRE_PIRANHAPLANT_BBOX_WIDTH / 2;
	}
	else
	{
		VxBullet = -0.05;
		nx = -1;
		BulletX = x - FIRE_PIRANHAPLANT_BBOX_WIDTH / 2;
	}
	BulletY = minY - 8;
	if (!fireBullet->isActivate)
	{
		fireBullet->isActivate = true;
		fireBullet->SetPosition(BulletX, BulletY);
		fireBullet->SetSpeed(VxBullet, VyBullet);
	}
}

