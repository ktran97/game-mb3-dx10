#include <algorithm>
#include "Mario.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!goingInsideHiddenMap && !goingOutOfHiddenMap)
	{
		allowedEnterToHiddenMap = false;

		vy += (float)ay * dt;
		vx += (float)ax * dt;

		HandleMarioStateIdle();
		HandleMarioTransformRacoon();
		HandleMarioSlowFalling();
		HandleMarioRunning();
		HandleMarioUntouchable();

		isOnPlatform = false;
		CCollision::GetInstance()->Process(this, dt, coObjects);

		HandleMarioKickKoopas();
		HandleRacoonAttack(dt, coObjects);
		HandleMarioHoldingKoopas();

		hud->speedStack = speedStack;
		hud->marioIsFlying = isFlying;

		Camera::GetInstance()->GetMarioAttributes(vx, vy, x, y, isOnPlatform, isFlying, isInsideHiddenMap);

		for (int i = 0; i < coObjects->size(); i++)
		{
			if (CCollision::GetInstance()->CheckAABB(this, coObjects->at(i)))
			{
				if (coObjects->at(i)->isitem)
				{
					if (dynamic_cast<Mushroom*>(coObjects->at(i)))
					{
						level = MARIO_LEVEL_BIG;
						if (level == MARIO_LEVEL_SMALL)
							y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
						coObjects->at(i)->Delete();
					}
					else if (dynamic_cast<Leaf*>(coObjects->at(i)))
					{
						if (level == MARIO_LEVEL_SMALL)
							y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
						SetState(MARIO_STATE_TRANSFORM_RACOON);
						coObjects->at(i)->Delete();
					}
				}
			}
		}
	}
	else
	{
		HandleMarioGoingIntoHiddenMap(dt);
	}
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}


void CMario::OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj) || e->obj->objType == OBJECT_TYPE_COIN)
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<QuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<Koopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<FirePiranhaPlant*>(e->obj))
		OnCollisionWithPlant(e);
	else if (dynamic_cast<BreakableBrick*>(e->obj))
		OnCollisionWithBreakableBrick(e);
	else if (dynamic_cast<ButtonP*>(e->obj))
		OnCollisionWithButtonP(e);
	else if (dynamic_cast<Mushroom*>(e->obj) || dynamic_cast<Leaf*>(e->obj))
		OnCollisionWithItem(e);
	else if (dynamic_cast<LastItem*>(e->obj))
		OnCollisionWithLastItem(e);
	else if (dynamic_cast<Pipe*>(e->obj))
		OnCollisionWithSpecialPipe(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->level == NORMAL_GOOMBA)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE) {
				goomba->SetState(GOOMBA_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else
		{
			goomba->level = NORMAL_GOOMBA;
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				HandleMarioIsAttacked();
			}
		}
	}
}



void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	DebugOut(L">>> Mario conllision with brick>>> \n");
	QuestionBrick* QBrick = dynamic_cast<QuestionBrick*>(e->obj);

	//Check qbrick
	if (!QBrick->innitItemSuccess && QBrick->GetState() != QUESTION_BRICK_STATE_START_INNIT) {
		if (e->ny > 0)
		{
			QBrick->SetState(QUESTION_BRICK_STATE_START_INNIT);
		}
	}
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	Koopas* koopas = dynamic_cast<Koopas*>(e->obj);
	if (e->ny < 0)
	{
		if (!isOnPlatform)
		{
			if (koopas->level < PARA_KOOPAS)
			{

				switch (koopas->GetState())
				{
				case KOOPAS_STATE_WALKING:
					koopas->SetState(KOOPAS_STATE_INSHELL);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
					break;
				case KOOPAS_STATE_INSHELL:
					koopas->nx = nx;
					koopas->SetState(KOOPAS_STATE_INSHELL_ATTACK);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
					break;
				case KOOPAS_STATE_INSHELL_ATTACK:
					koopas->SetState(KOOPAS_STATE_INSHELL);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
					break;
				default:
					break;
				}
			}
			else {
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				koopas->SetSpeed(0, 0);
				koopas->level = NORMAL_KOOPAS;
				koopas->SetState(KOOPAS_STATE_WALKING);
			}
		}
	}
	else // hit by Koopas
	{
		if (untouchable == 0)
		{
			if (koopas->IsAttack)
			{
				HandleMarioIsAttacked();
			}
		}
		if (e->nx != 0 && !koopas->IsAttack)
		{
			if (abs(ax) != MARIO_ACCEL_RUN_X)
			{
				koopas->nx = nx;
				SetState(MARIO_STATE_KICKKOOPAS);
				koopas->SetState(KOOPAS_STATE_INSHELL_ATTACK);
			}
			else if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				koopas->SetSpeed(0, 0);
				isHoldingKoopas = true;
				koopas->setIsHold(true);
				koopasHold = dynamic_cast<Koopas*>(e->obj);
				DebugOut(L">>>mario is holding koopas >>> \n");
			}
		}
	}
}

void CMario::OnCollisionWithItem(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<Mushroom*>(e->obj))
	{
		DebugOut(L">>> mario conllison with mushroom >>> \n");
		if (level == MARIO_LEVEL_SMALL)
			y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
		level = MARIO_LEVEL_BIG;
		DebugOut(L">>> small mario transform into BIG MARIO>>> \n");
		e->obj->Delete();
	}
	else if (dynamic_cast<Leaf*>(e->obj))
	{
		DebugOut(L">>> Mario conllison with leaf >>> \n");
		if (level == MARIO_LEVEL_SMALL)
		{
			y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			SetState(MARIO_STATE_TRANSFORM_RACOON);
		}
		else
		{
			DebugOut(L">>> racoon keep current state >>> \n");
		}
		e->obj->Delete();
	}
}

void CMario::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	if (untouchable == 0)
	{
		HandleMarioIsAttacked();
	}
}

void CMario::OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e)
{
	if (e->ny > 0)
	{
		BreakableBrick* breakableBrick = dynamic_cast<BreakableBrick*>(e->obj);
		if (breakableBrick->haveButton && !breakableBrick->buttonCreated)
		{
			breakableBrick->SetState(BREAKABLE_BRICK_STATE_CREATE_BUTTON);
		}
		else if (!breakableBrick->haveButton) {
			e->obj->SetState(BREAKABLE_BRICK_STATE_BREAK_DOWN);
		}
	}
}

void CMario::OnCollisionWithButtonP(LPCOLLISIONEVENT e)
{
	if (e->ny < 0 && !ButtonP::GetInstance()->isPushed)
	{
		ButtonP::GetInstance()->SetState(BUTTON_P_STATE_PUSHED);
	}
}

void CMario::OnCollisionWithLastItem(LPCOLLISIONEVENT e)
{
	LastItem* LT = dynamic_cast<LastItem*>(e->obj);
	if (!LT->isChosen)
	{
		LT->isChosen = true;
	}
}

void CMario::OnCollisionWithSpecialPipe(LPCOLLISIONEVENT e)
{
	Pipe* pipe = dynamic_cast<Pipe*>(e->obj);
	if (pipe->PipeType == SPECIAL_PIPE && e->ny < 0)
	{
		startY = y + MARIO_BIG_BBOX_HEIGHT;
		pipeX = pipe->x;
		allowedEnterToHiddenMap = true;
	}
	else if (pipe->PipeType == SPECIAL_PIPE_HIDDEN_MAP_PIPE && e->ny > 0) 
	{
		startY = pipe->y;
		allowedEnterToHiddenMap = true;
		pipeX = pipe->x;
	}
}



//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else if (isSitting)
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_SIT_RIGHT;
		else
			aniId = ID_ANI_MARIO_SIT_LEFT;
	}
	else
	{
		if (vx == 0)
		{
			if (isHoldingKoopas)
			{
				//HOLDING KOOPAS WHEN MARIO SMALL STAND STILL
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLDKOOPAS_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_HOLDKOOPAS_IDLE_LEFT;
			}
			else
			{
				if (state == MARIO_STATE_IDLE)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
				else if (state == MARIO_STATE_RUNNING_RIGHT || state == MARIO_STATE_WALKING_RIGHT)
				{
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}
				else if (state == MARIO_STATE_RUNNING_LEFT || state == MARIO_STATE_WALKING_LEFT)
				{
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
			}
		}
		else if (vx > 0)
		{
			if (isHoldingKoopas)
			{
				//HOLDING KOOPAS WHEN SMALL MARIO RUN
				DebugOut(L">>> small is holding koopas shell & walking >>> \n ");
				if (ax == -MARIO_ACCEL_WALK_X || ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_HOLDKOOPAS_JUMP_LEFT;
				else
					aniId = ID_ANI_MARIO_SMALL_HOLDKOOPAS_WALK_RIGHT;
			}
			else
			{
				if (ax < 0 && state != MARIO_STATE_IDLE)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X || ax == -MARIO_ACCEL_SLOWING_DOWN_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
				{
					if (speedStack == MARIO_MAX_SPEED_STACK - 4)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
					else
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}
			}
		}
		else if (vx < 0)
		{
			if (isHoldingKoopas)
			{
				if (ax == MARIO_ACCEL_WALK_X || ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_HOLDKOOPAS_JUMP_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_HOLDKOOPAS_WALK_LEFT;
			}
			else
			{
				if (ax > 0 && state != MARIO_STATE_IDLE)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X || ax == MARIO_ACCEL_SLOWING_DOWN_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					if (speedStack == MARIO_MAX_SPEED_STACK)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
					else
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
			}
		}
	}

	if (IsKickKoopas) {
		if (nx > 0)
			aniId = ID_ANI_MARIO_SMALL_KICKKOOPAS_RIGHT;
		else
			aniId = ID_ANI_MARIO_SMALL_KICKKOOPAS_LEFT;
	}

	if (state == MARIO_STATE_TRANSFORM_RACOON || state == RACOON_STATE_TRANSFORM_MARIO)
	{
		aniId = ID_ANI_RACOON_EFFECT_WHEN_ATTACKED;
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID for Racoon
//
int CMario::GetAniIdRacoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (vy >= 0)
		{
			if (!isHoldingKoopas)
			{
				if (!isSitting)
				{
					if (nx >= 0)
						aniId = ID_ANI_RACOON_FALLING_RIGHT;
					else
						aniId = ID_ANI_RACOON_FALLING_LEFT;
				}
				else {
					if (nx > 0)
						aniId = ID_ANI_RACOON_SITTING_RIGHT;
					else
						aniId = ID_ANI_RACOON_SITTING_LEFT;
				}
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_RACOON_HOLDKOOPAS_JUMP_RIGHT;
				else
					aniId = ID_ANI_RACOON_HOLDKOOPAS_JUMP_LEFT;
			}
		}
		else {
			if (!isHoldingKoopas)
			{
				if (!isSitting)
				{

					if (nx >= 0)
						aniId = ID_ANI_RACOON_JUMP_WALK_RIGHT;
					else
						aniId = ID_ANI_RACOON_JUMP_WALK_LEFT;
				}
				else {
					if (nx > 0)
						aniId = ID_ANI_RACOON_SITTING_RIGHT;
					else
						aniId = ID_ANI_RACOON_SITTING_LEFT;
				}
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_RACOON_HOLDKOOPAS_JUMP_RIGHT;
				else
					aniId = ID_ANI_RACOON_HOLDKOOPAS_JUMP_LEFT;
			}
		}
		if (isFlying)
		{
			if (vy > 0)
			{
				if (nx > 0)aniId = ID_ANI_RACOON_FALLING_FLYING_RIGHT;
				else aniId = ID_ANI_RACOON_FALLING_FLYING_LEFT;
			}
			else if (vy < 0)
			{
				if (nx > 0)aniId = ID_ANI_RACOON_FLYING_RIGHT;
				else aniId = ID_ANI_RACOON_FLYING_LEFT;
			}
		}
	}
	else
	{
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_RACOON_SITTING_RIGHT;
			else
				aniId = ID_ANI_RACOON_SITTING_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (state == MARIO_STATE_IDLE)
				{
					//TODO: NOT HANDLE RACOON HAVE COULD ATTACKED KOOPAS YET
					if (isHoldingKoopas)
					{
						//HOLDING KOOPAS WHEN RACOON STAND STILL
						if (nx > 0) aniId = ID_ANI_RACOON_HOLDKOOPAS_IDLE_RIGHT;
						else aniId = ID_ANI_RACOON_HOLDKOOPAS_IDLE_LEFT;
					}
					else
					{
						if (nx > 0) aniId = ID_ANI_RACOON_IDLE_RIGHT;
						else aniId = ID_ANI_RACOON_IDLE_LEFT;
					}
				}
				else if (state == MARIO_STATE_RUNNING_RIGHT || state == MARIO_STATE_WALKING_RIGHT)
				{
					if (isHoldingKoopas)
					{
						aniId = ID_ANI_RACOON_HOLDKOOPAS_WALK_RIGHT;
					}
					else
					{
						aniId = ID_ANI_RACOON_WALKING_RIGHT;
					}
				}
				else if (state == MARIO_STATE_RUNNING_LEFT || state == MARIO_STATE_WALKING_LEFT)
				{
					if (isHoldingKoopas)
					{
						aniId = ID_ANI_RACOON_HOLDKOOPAS_WALK_LEFT;
					}
					else
					{
						aniId = ID_ANI_RACOON_WALKING_LEFT;
					}
				}
			}
			else if (vx > 0)
			{
				if (isHoldingKoopas)
				{
					//HOLDING KOOPAS WHEN RACOON RUN
					if (ax == -MARIO_ACCEL_WALK_X || ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_RACOON_HOLDKOOPAS_JUMP_LEFT;
					else
						aniId = ID_ANI_RACOON_HOLDKOOPAS_WALK_RIGHT;
				}
				else
				{
					if (ax == -MARIO_ACCEL_WALK_X || ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_RACOON_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_RACOON_WALKING_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
					{
						if (speedStack == MARIO_MAX_SPEED_STACK)
							aniId = ID_ANI_RACOON_RUNNING_RIGHT;
						else
							aniId = ID_ANI_RACOON_WALKING_RIGHT;
					}
					else if (ax == -MARIO_ACCEL_SLOWING_DOWN_X)
						aniId = ID_ANI_RACOON_WALKING_RIGHT;
				}
			}
			else // vx < 0
			{
				if (isHoldingKoopas)
				{
					if (ax == MARIO_ACCEL_WALK_X || ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_RACOON_HOLDKOOPAS_JUMP_RIGHT;
					else
						aniId = ID_ANI_RACOON_HOLDKOOPAS_WALK_LEFT;
				}
				else
				{
					if (ax == MARIO_ACCEL_WALK_X || ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_RACOON_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_RACOON_WALKING_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
					{
						if (speedStack == MARIO_MAX_SPEED_STACK)
							aniId = ID_ANI_RACOON_RUNNING_LEFT;
						else
							aniId = ID_ANI_RACOON_WALKING_LEFT;
					}
					else if (ax == MARIO_ACCEL_SLOWING_DOWN_X)
						aniId = ID_ANI_RACOON_WALKING_LEFT;
				}
			}
		}

	}
	//ANI SLOW FALLING
	if (IsSlowFalling)
	{
		DebugOut(L">>> RACOON IS SLOW FALLING >>> \n");
		if (nx > 0)
			aniId = ID_ANI_RACOON_SLOWFALLING_RIGHT;
		else
			aniId = ID_ANI_RACOON_SLOWFALLING_LEFT;
	}
	//ANI KICK KOOPAS
	if (IsKickKoopas) {
		DebugOut(L">>> RACOON IS KICKING >>> \n");
		if (nx > 0)
			aniId = ID_ANI_RACOON_KICKKOOPAS_RIGHT;
		else
			aniId = ID_ANI_RACOON_KICKKOOPAS_LEFT;
	}

	if (aniId == -1) aniId = ID_ANI_RACOON_IDLE_RIGHT;
	//ANI RACOON ATK
	if (IsAttack)
	{
		if (level == MARIO_LEVEL_RACOON) {
			DebugOut(L">>> RACOON IS ATK >>> \n");
			if (nx > 0)aniId = ID_ANI_RACOON_ATTACK_RIGHT;
			else aniId = ID_ANI_RACOON_ATTACK_LEFT;
		}
	}
	//ANI RACOON IS FLYING
	if (isFlying)
	{
		if (vy > 0)
		{
			if (nx > 0)
			{
				aniId = ID_ANI_RACOON_FLYING_RIGHT;
			}
			else
			{
				aniId = ID_ANI_RACOON_FLYING_LEFT;
			}
		}
		else if (vy < 0)
		{
			if (nx > 0)
			{
				aniId = ID_ANI_RACOON_FLYING_RIGHT;
			}
			else
			{
				aniId = ID_ANI_RACOON_FLYING_LEFT;
			}
		}
	}

	if (state == MARIO_STATE_TRANSFORM_RACOON || state == RACOON_STATE_TRANSFORM_MARIO)
	{
		aniId = ID_ANI_RACOON_EFFECT_WHEN_ATTACKED;
	}

	return aniId;
}

//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
	{
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (state == MARIO_STATE_IDLE)
				{
					if (isHoldingKoopas)
					{
						//HOLDING KOOPAS WHEN MARIO STAND STILL
						if (nx > 0) aniId = ID_ANI_MARIO_HOLDKOOPAS_IDLE_RIGHT;
						else aniId = ID_ANI_MARIO_HOLDKOOPAS_IDLE_LEFT;
					}
					else
					{
						if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
						else aniId = ID_ANI_MARIO_IDLE_LEFT;
					}
				}
				else if (state == MARIO_STATE_RUNNING_RIGHT || state == MARIO_STATE_WALKING_RIGHT)
				{
					if (isHoldingKoopas)
					{
						aniId = ID_ANI_MARIO_HOLDKOOPAS_WALK_RIGHT;
					}
					else
					{
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
					}
				}
				else if (state == MARIO_STATE_RUNNING_LEFT || state == MARIO_STATE_WALKING_LEFT)
				{
					if (isHoldingKoopas)
					{
						aniId = ID_ANI_MARIO_HOLDKOOPAS_WALK_LEFT;
					}
					else
					{
						aniId = ID_ANI_MARIO_WALKING_LEFT;
					}
				}
			}
			else if (vx > 0)
			{
				if (isHoldingKoopas)
				{
					//HOLDING KOOPAS WHEN MARIO RUN
					if (ax == -MARIO_ACCEL_WALK_X || ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_HOLDKOOPAS_JUMP_LEFT;
					else
						aniId = ID_ANI_MARIO_HOLDKOOPAS_WALK_RIGHT;
				}
				else
				{
					if (ax == -MARIO_ACCEL_WALK_X || ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
					{
						if (speedStack == MARIO_MAX_SPEED_STACK)
							aniId = ID_ANI_MARIO_RUNNING_RIGHT;
						else
							aniId = ID_ANI_MARIO_WALKING_RIGHT;
					}
					else if (ax == -MARIO_ACCEL_SLOWING_DOWN_X)
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
				}
			}
			else if (vx < 0)
			{
				if (isHoldingKoopas)
				{
					if (ax == MARIO_ACCEL_WALK_X || ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_HOLDKOOPAS_JUMP_RIGHT;
					else
						aniId = ID_ANI_MARIO_HOLDKOOPAS_WALK_LEFT;
				}
				else
				{
					if (ax == MARIO_ACCEL_WALK_X || ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
					{
						if (speedStack == MARIO_MAX_SPEED_STACK)
							aniId = ID_ANI_MARIO_RUNNING_LEFT;
						else
							aniId = ID_ANI_MARIO_WALKING_LEFT;
					}
					else if (ax == MARIO_ACCEL_SLOWING_DOWN_X)
						aniId = ID_ANI_MARIO_WALKING_LEFT;
				}
			}
		}
	}

	if (IsKickKoopas) {
		if (nx > 0)
			aniId = ID_ANI_MARIO_KICKKOOPAS_RIGHT;
		else
			aniId = ID_ANI_MARIO_KICKKOOPAS_LEFT;
	}

	if (state == MARIO_STATE_TRANSFORM_RACOON || state == RACOON_STATE_TRANSFORM_MARIO)
	{
		aniId = ID_ANI_RACOON_EFFECT_WHEN_ATTACKED;
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (!IsAttack && level == MARIO_LEVEL_RACOON)
	{
		animations->Get(ID_ANI_RACOON_ATTACK_LEFT)->ResetAni();
		animations->Get(ID_ANI_RACOON_ATTACK_RIGHT)->ResetAni();
	}

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIdRacoon();

	if (animations->Get(aniId))
	{
		animations->Get(aniId)->Render(x, y);
	}

	RenderBoundingBox();

	if (IsAttack)tail->Render();

	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
		//RUNNING
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;

		//WALKING
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting)
		{
			isSitting = false;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting)
		{
			isSitting = false;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;

	case MARIO_STATE_JUMP:
		if (isOnPlatform)
		{
			if (abs(vx) >= MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0 && !isFlying) vy = 0;
		ay = MARIO_GRAVITY;
		break;

	case MARIO_STATE_SIT:
		if (this->state == MARIO_STATE_WALKING_LEFT || this->state == MARIO_STATE_WALKING_RIGHT)
			break;
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f; ax = 0;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;
	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		if (vx != 0) {
			ax = -nx * (float)MARIO_ACCEL_SLOWING_DOWN_X;
		}
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;

		break;
	case MARIO_STATE_KICKKOOPAS:
		vx = 0;
		ax = 0;
		KickKoopasTime = GetTickCount64();
		IsKickKoopas = true;
		break;

	case MARIO_STATE_ATTACK:
		if (level == MARIO_LEVEL_RACOON)
		{
			IsAttack = true;
			AttackTime = GetTickCount64();
			tail->IsActive = true;
		}
		break;

	case MARIO_STATE_SLOW_FALLING:
		ay = 0;
		vy = MARIO_SLOW_FALLING_SPEED;
		IsSlowFalling = true;
		SlowFallingTime = GetTickCount64();
		break;

	case MARIO_STATE_FLYING:
		vy = -MARIO_FLYING_SPEED;
		ay = 0;
		IsFalling = true;
		FallingTime = GetTickCount64();
		if (!isFlying)
		{
			isFlying = true;
			FlyingTime = GetTickCount64();
		}
		break;

	case MARIO_STATE_RELEASE_KOOPAS:
		float koopasY;
		isHoldingKoopas = false;
		koopasHold->setIsHold(false);
		koopasHold->nx = nx;
		if (level == MARIO_LEVEL_SMALL)
			koopasY = y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
		else koopasY = y;
		koopasHold->SetPosition(koopasHold->x + KOOPAS_BBOX_WIDTH / 8, koopasY);
		koopasHold->SetState(KOOPAS_STATE_INSHELL_ATTACK);
		break;

		//TRANSFORM
	case MARIO_STATE_TRANSFORM_RACOON:
		effectTime = GetTickCount64();
		vx = vy = ax = ay = 0;
		break;
	case RACOON_STATE_TRANSFORM_MARIO:
		effectTime = GetTickCount64();
		vx = vy = ax = ay = 0;
		break;
	case MARIO_STATE_GOING_INSIDE_HIDDEN_MAP:
		goingInsideHiddenMap = true;
		SetPosition(pipeX, y);
		break;
	case MARIO_STATE_GOING_OUT_OF_HIDDEN_MAP:
		goingOutOfHiddenMap = true;
		SetPosition(pipeX, y);
		break;
	}
	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_RACOON)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2 - 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2 - 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH + 2;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT + 2;
		}
		else
		{
			if (nx > 0)
				left = x - MARIO_BIG_BBOX_WIDTH / 2 + 4;
			else
				left = x - MARIO_BIG_BBOX_WIDTH / 2 - 2;
			right = left + MARIO_BIG_BBOX_WIDTH - 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

void CMario::IncreaseSpeedStack() {
	if (speedStack < MARIO_MAX_SPEED_STACK)
	{
		if (SpeedStackTime == 0)SpeedStackTime = GetTickCount64();
		else if (GetTickCount64() - SpeedStackTime > MARIO_SPEEDSTACK_TIME)
		{
			SpeedStackTime = 0;
			speedStack++;
		}
	}
	else {
		DebugOut(L">>> MARIO MAX SPEED STACK >>> \n");
	}
}

void CMario::DecreaseSpeedStack() {
	if (SpeedStackTime == 0)SpeedStackTime = GetTickCount64();
	else if (GetTickCount64() - SpeedStackTime > MARIO_SPEEDSTACK_TIME)
	{
		SpeedStackTime = 0;
		speedStack--;
	}
}

void CMario::HandleMarioIsAttacked()
{
	if (level > MARIO_LEVEL_BIG)
	{
		StartUntouchable();
		SetState(RACOON_STATE_TRANSFORM_MARIO);
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		StartUntouchable();
		level = MARIO_LEVEL_SMALL;
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		SetState(MARIO_STATE_DIE);
		DebugOut(L">>>mario die>>> \n");
	}
}

void CMario::HandleMarioIsFlying(DWORD dt)
{
	if (isFlying)
	{
		if (GetTickCount64() - FlyingTime >= 3000)
		{
			isFlying = false;
			if (!isOnPlatform)
			{
				SetState(MARIO_STATE_RELEASE_JUMP);
			}
		}
	}
}

void CMario::HandleMarioTransformRacoon()
{
	if (state == MARIO_STATE_TRANSFORM_RACOON || state == RACOON_STATE_TRANSFORM_MARIO)
	{
		if (GetTickCount64() - effectTime > RACOON_IS_ATTACKED_TIME)
		{
			if (state == RACOON_STATE_TRANSFORM_MARIO)
				level = MARIO_LEVEL_BIG;
			else
				level = MARIO_LEVEL_RACOON;
			ay = MARIO_GRAVITY;
			SetState(MARIO_STATE_IDLE);
		}
	}
}

void CMario::HandleMarioSlowFalling()
{
	if (IsSlowFalling)
	{
		if (GetTickCount64() - SlowFallingTime >= MARIO_SLOWFALLING_TIME)
		{
			IsSlowFalling = false;
			SetState(MARIO_STATE_RELEASE_JUMP);
		}
	}
}

void CMario::HandleMarioUntouchable()
{
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
}

void CMario::HandleMarioKickKoopas()
{
	//KICK KOOPAS
	if (IsKickKoopas)
	{
		if (GetTickCount64() - KickKoopasTime >= MARIO_KICK_KOOPAS_TIME)
		{
			IsKickKoopas = false;
		}
	}
}

void CMario::HandleRacoonAttack(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//ATTACK
	if (IsAttack)
	{
		if (nx > 0)
			tail->SetPosition(x + MARIO_BIG_BBOX_WIDTH / 2 + TAIL_BBOX_WIDTH / 2, y + 5);
		else
			tail->SetPosition(x - MARIO_BIG_BBOX_WIDTH / 2 - TAIL_BBOX_WIDTH / 2, y + 5);
		tail->Update(dt, coObjects);
		if (GetTickCount64() - AttackTime >= RACOON_ATTACK_TIME)
		{
			IsAttack = false;
		}
	}
}

void CMario::HandleMarioHoldingKoopas()
{
	//HOLDING KOOPAS
	if (CheckMarioHoldKoopas())
	{
		float koopasX, koopasY;
		if (level == MARIO_LEVEL_SMALL)
			koopasY = y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
		else
			koopasY = y;
		if (level == MARIO_LEVEL_RACOON)
		{
			koopasX = x;
		}
		else {
			if (nx > 0)
				koopasX = x - KOOPAS_BBOX_WIDTH / 4;
			else
				koopasX = x + KOOPAS_BBOX_WIDTH / 4;
		}
		if (nx > 0)
			koopasHold->SetPosition(koopasX + MARIO_BIG_BBOX_WIDTH / 2 + KOOPAS_BBOX_WIDTH / 2, koopasY);
		else
			koopasHold->SetPosition(koopasX - MARIO_BIG_BBOX_WIDTH, koopasY);
		if (koopasHold->GetState() == KOOPAS_STATE_WALKING)
		{
			koopasHold->y -= ((KOOPAS_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT) / 2);
			isHoldingKoopas = false;
			//HANDLE MARIO IS ATTACKED WHEN HOLDING KOOPAS SHELL
			HandleMarioIsAttacked();
		}
	}
}

void CMario::HandleMarioStateIdle()
{
	if (abs(vx) > abs(maxVx) && state != MARIO_STATE_IDLE) vx = maxVx;
	if (state == MARIO_STATE_IDLE) {
		if (nx > 0 && vx < 0) { vx = 0; ax = 0; }
		else if (nx < 0 && vx > 0) { vx = 0; ax = 0; }
	}
}

void CMario::HandleMarioRunning()
{
	if (abs(ax) == MARIO_ACCEL_RUN_X && abs(vx) > MARIO_WALKING_SPEED)
	{
		IncreaseSpeedStack();
	}
	else {
		if (speedStack > 0)
		{
			if (!isFlying)
				DecreaseSpeedStack();
		}
	}
}

void CMario::HandleMarioGoingIntoHiddenMap(DWORD dt)
{
	if (goingInsideHiddenMap)
	{
		vy = MARIO_GO_HIDDEN_MAP_SPEED;
		vx = 0;
		if (y - startY >= MARIO_BIG_BBOX_HEIGHT / 2)
		{
			SetPosition(HIDDEN_MAP_START_POS_X, HIDDEN_MAP_START_POS_Y);
			startY = 1000;
			isInsideHiddenMap = true;
			Camera::GetInstance()->GetMarioAttributes(vx, vy, x, y, isOnPlatform, isFlying, isInsideHiddenMap);
		}
		if (y - HIDDEN_MAP_START_POS_Y >= MARIO_BIG_BBOX_HEIGHT)
		{
			goingInsideHiddenMap = false;
		}
	}
	else if (goingOutOfHiddenMap)
	{
		vy = -(float)MARIO_GO_HIDDEN_MAP_SPEED;
		vx = 0;
		if (startY - y >= MARIO_BIG_BBOX_HEIGHT)
		{
			isInsideHiddenMap = false;
			SetPosition(HIDDEN_MAP_OUT_POS_X, HIDDEN_MAP_OUT_POS_Y);
			startY = 0;
			Camera::GetInstance()->GetMarioAttributes(vx, vy, x, y, isOnPlatform, isFlying, isInsideHiddenMap);
		}
		if (HIDDEN_MAP_OUT_POS_Y - y >= 16 * 2)
		{
			goingOutOfHiddenMap = false;
		}
	}
	y += vy * dt;
}