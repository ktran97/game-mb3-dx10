#pragma once
#include <iostream>
#include <fstream>

#include "AssetIDs.h"
#include "Animation.h"
#include "Animations.h"
#include "Scene.h"
#include "Textures.h"
#include "Game.h"
#include "debug.h"
#include "AssetIDs.h"

#define SCENE_SECTION_UNKNOWN		-1
#define SCENE_SECTION_TEXTURES		2
#define SCENE_SECTION_SPRITES		3
#define SCENE_SECTION_ANIMATIONS	4
#define SCENE_SECTION_OBJECTS		6
#define SCENE_SECTION_ASSETS		7

#define MAX_SCENE_LINE				1024

#define ID_SPRITE_INTRO_BACKGROUND	10001
#define ID_SPRITE_INTRO_ARROW		10101
#define ID_ANIMATION_NUM_3			10201

#define ONE_PLAYER_MODE				1
#define TWO_PLAYER_MODE				2

class CIntroScene : public CScene
{
protected:
	LPSPRITE backgroundSprite = NULL;
	LPSPRITE onePlayerArrowSprite = NULL;
	LPSPRITE twoPlayerArrowSprite = NULL;

	LPANIMATION num3Ani = NULL;

	int currentMode = ONE_PLAYER_MODE;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

public:
	CIntroScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void SetMode(int mode) { currentMode = mode; }
	int GetMode() { return currentMode; }
};

class CIntroSceneKeyHandler : public CSceneKeyHandler
{
public:

	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	CIntroSceneKeyHandler(CScene* s) :CSceneKeyHandler(s) {};
};