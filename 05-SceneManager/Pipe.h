#pragma once
#include "GameObject.h"

#define ID_SPRITE_PIPE_MOUTH	131313
#define ID_SPRITE_PIPE_BODY		141414

#define ID_SPRITE_HIDDEN_MAP_PIPE_MOUTH		232323
#define ID_SPRITE_HIDDEN_MAP_PIPE_BODY		242424

#define SPRITE_TILE_SIZE	16

#define NORMAL_PIPE						1
#define HIDDEN_MAP_PIPE					2
#define SPECIAL_PIPE					3
#define SPECIAL_PIPE_HIDDEN_MAP_PIPE	4

class Pipe :
	public CGameObject
{
public:
	int Width, Height;
	int TitleSize = SPRITE_TILE_SIZE;
	int PipeType;

	Pipe(float x, float y, int width, int height, int type);

	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsBlocking()
	{
		return 1;
	};

	int IsCollidable()
	{
		return 1;
	};
};

