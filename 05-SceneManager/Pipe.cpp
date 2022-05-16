#include "Pipe.h"

Pipe::Pipe(float x, float y, int width, int height) : CGameObject(x, y) {
	this->Width = width;
	this->Height = height;
}


void Pipe::Render() {
	CSprites* sprite = CSprites::GetInstance();
	int SpriteY = y - Height / 2 + SPRITE_TILE_SIZE / 2;
	for (int i = 0; i < Height / SPRITE_TILE_SIZE; i++)
	{
		if (i < 1)
			sprite->Get(ID_SPRITE_PIPE_MOUTH)->Draw(x, SpriteY);
		else
			sprite->Get(ID_SPRITE_PIPE_BODY)->Draw(x, SpriteY);
		SpriteY += SPRITE_TILE_SIZE;
	}
};

void Pipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - Width / 2;
	t = y - Height / 2;
	r = l + Width;
	b = t + Height;
}

void Pipe::Update(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

