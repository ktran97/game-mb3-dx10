#pragma once
#include "GameObject.h"
class ColorBox :
	public CGameObject
{
	int Width;
	int Height;
public:
	ColorBox(int W, int H);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual int GetWidth() { return Width; };
	virtual void Render();
	virtual void DirectBlocking(int& l, int& t, int& r, int& b) { l = 0; t = 1; b = 0; r = 0; }
};