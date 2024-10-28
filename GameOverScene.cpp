#include "GameOverScene.h"
#include "Engine/SceneManager.h"
#include "Player.h"

GameOverScene::GameOverScene(GameObject* parent)
{
	over = LoadGraph("Assets/GameOver.png");
	s = LoadGraph("Assets/s.png");
	q = LoadGraph("Assets/q.png");
	counter = 0;
}

void GameOverScene::Initialize()
{
}

void GameOverScene::Update()
{
	if (CheckHitKey(KEY_INPUT_Q))
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

void GameOverScene::Draw()
{
	DrawGraph(150, 200, over, TRUE);
	DrawGraph(150, 400, s, TRUE);
	DrawGraph(260, 500, q, TRUE);
}

void GameOverScene::Release()
{
}
