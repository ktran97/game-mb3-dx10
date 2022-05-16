#include "ColorBox.h"
ColorBox::ColorBox(int W, int H)
{
	this->Width = W;
	this->Height = H;
	this->objType = 6;
}

void ColorBox::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - Width / 2;
	top = y - Height / 2;
	right = left + Width;
	bottom = top + Height;
}

void ColorBox::Render()
{
	//RenderBoundingBox();
}
