#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Map.h"

#define SCENE_SECTION_UNKNOWN		-1
#define SCENE_SECTION_TEXTURES		1
#define SCENE_SECTION_SPRITES		2
#define SCENE_SECTION_ANIMATIONS	3
#define SCENE_SECTION_OBJECTS		4
#define SCENE_SECTION_MAP			5

#define MAX_SCENE_LINE 1024

class CWorldMapScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;

	vector<LPGAMEOBJECT> objects;

	vector<LPGAMEOBJECT> Pipes;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);

public:
	CWorldMapScene(int id, LPCWSTR filePath);
	Map* map;
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

class CWorldMapSceneKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CWorldMapSceneKeyHandler(CScene* s) :CSceneKeyHandler(s) {};
};

typedef CWorldMapScene* LPWORLDSCENE;
