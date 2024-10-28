#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Player.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent, "TitleScene")
{
	title = LoadGraph("Assets/Title.png");
	mori = LoadGraph("Assets/mori1.jpg");
	moji1 = LoadGraph("Assets/Start.png");
	moji2 = LoadGraph("Assets/exit.png");
}

void TitleScene::Initialize()
{
}

void TitleScene::Update()
{
	//Player* pPlayer = GetParent()->FindGameObject<Player>();
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
		//pPlayer->Player();
		//CheckHitKey
	}

	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		exit(0);
	}
}

void TitleScene::Draw()
{
	DrawGraph(0, 0, mori, TRUE);
	DrawGraph(100, 200, title, TRUE);
	DrawGraph(200, 400, moji1, TRUE);
	DrawGraph(200, 500, moji2, TRUE);
}

void TitleScene::Release()
{
}
