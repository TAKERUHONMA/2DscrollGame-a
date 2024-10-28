#include "GameClear.h"
#include "Engine/SceneManager.h"

GameClear::GameClear(GameObject* parent)
{
	clear = LoadGraph("Assets/Clear.png");
	mori = LoadGraph("Assets/mori1.jpg");
	s = LoadGraph("Assets/s.png");
	e = LoadGraph("Assets/e.png");
}

void GameClear::Initialize()
{
}

void GameClear::Update()
{
	if (CheckHitKey(KEY_INPUT_E))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
}

void GameClear::Draw()
{
	DrawGraph(0, 0, mori, TRUE);
	DrawGraph(150, 200, clear, TRUE);
	DrawGraph(150, 400, s, TRUE);
	DrawGraph(260, 500, e, TRUE);
}

void GameClear::Release()
{
}
