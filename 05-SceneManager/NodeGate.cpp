#include "NodeGate.h"

CNodeGate::CNodeGate(int id, bool left, bool top, bool right, bool bottom)
{
	sceneId = id;
	allowedToLeft = left;
	allowedToTop = top;
	allowedToRight = right;
	allowedToBottom = bottom;
}

void CNodeGate::Render()
{
	RenderBoundingBox();
}

void CNodeGate::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - WORLD_STATION_BBOX_WIDTH / 2;
	top = y - WORLD_STATION_BBOX_HEIGHT / 2;
	right = left + WORLD_STATION_BBOX_WIDTH;
	bottom = top + WORLD_STATION_BBOX_HEIGHT;
}