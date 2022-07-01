#include "Intro.h"


CIntroScene::CIntroScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CIntroSceneKeyHandler(this);
}


void CIntroScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return;

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CIntroScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return;

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CIntroScene::_ParseSection_OBJECTS(string line)
{
}

void CIntroScene::_ParseSection_ASSETS(string line)
{
}

void CIntroScene::Load()
{
	ifstream f;
	f.open(sceneFilePath);

	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue; // skip comment lines	
		if (line == "[SPRITES]") { section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; }
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		}
	}

	f.close();

	backgroundSprite = CSprites::GetInstance()->Get(ID_SPRITE_INTRO_BACKGROUND);
	onePlayerArrowSprite = CSprites::GetInstance()->Get(ID_SPRITE_INTRO_ARROW);
	twoPlayerArrowSprite = CSprites::GetInstance()->Get(ID_SPRITE_INTRO_ARROW);
	num3Ani = CAnimations::GetInstance()->Get(ID_ANIMATION_NUM_3);

	Camera::GetInstance()->SetCamPos(0, 0);
}

void CIntroScene::Update(DWORD dt)
{
}

void CIntroScene::Render()
{
	backgroundSprite->Draw(125, 116);
	num3Ani->Render(124, 119);

	switch (currentMode)
	{
	case ONE_PLAYER_MODE:onePlayerArrowSprite->Draw(61, 159); break;
	case TWO_PLAYER_MODE:onePlayerArrowSprite->Draw(61, 178); break;
	default:
		break;
	}
}

void CIntroScene::Unload()
{
	backgroundSprite = NULL;
	onePlayerArrowSprite = NULL;
	twoPlayerArrowSprite = NULL;
	num3Ani = NULL;
}

void CIntroSceneKeyHandler::KeyState(BYTE* states)
{
}

void CIntroSceneKeyHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_UP:
		((CIntroScene*)scence)->SetMode(ONE_PLAYER_MODE);
		break;
	case DIK_DOWN:
		((CIntroScene*)scence)->SetMode(TWO_PLAYER_MODE);
		break;
	case DIK_W:
		switch (((CIntroScene*)scence)->GetMode())
		{
		case ONE_PLAYER_MODE:
			CGame::GetInstance()->SwitchScene(SCENE_ID_MAP_1_1);
			break;
		case TWO_PLAYER_MODE:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void CIntroSceneKeyHandler::OnKeyUp(int KeyCode)
{
}