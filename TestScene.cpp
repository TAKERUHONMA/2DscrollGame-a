#include "TestScene.h"
#include "Player.h"
#include "Enemy1.h"
#include "Field.h"
#include "Camera.h"
#include "Banner.h"
#include "Engine/SceneManager.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<Camera>(this);
	Field* pField = Instantiate<Field>(this);
	Instantiate<Player>(this);
	pField->Reset();
	Instantiate<Banner>(this);
	StartReady();
}

//更新
void TestScene::Update()
{
	switch (state) {
	case S_Ready:UpdateReady(); break;
	case S_Play:UpdatePlay(); break;
	case S_Clear: UpdateClear(); break;
	case S_Dead: UpdateDead(); break;
	}
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}

bool TestScene::CanMove()
{
	return (state == S_Play);
}

void TestScene::StartReady()
{
	readyTimer = 1.5f;
	state = S_Ready;
}

void TestScene::UpdateReady()
{
	readyTimer -= 1.0f / 60.0f;
	if (readyTimer <= 0.0f) 
	{
		StartPlay();
	}
}

void TestScene::StartPlay()
{
	state = S_Play;
	//Banner* bn = FindGameObject<Banner>();
	//bn->View(Banner::ViewID::V_Nothing);
}

void TestScene::UpdatePlay()
{
}

//void TestScene::StartClear()
//{
//	readyTimer = 1.5f;
//	state = S_Clear;
//}

void TestScene::UpdateClear()
{
	//readyTimer -= 1.0f / 60.0f;
	//if (readyTimer <= 0.0f)
	//{
	//	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	//	pSceneManager->ChangeScene(SCENE_ID_GAMECLEAR);
	//}
}

void TestScene::StartDead()
{
	readyTimer = 1.5f;
	state = S_Dead;
	//Banner* bn = FindGameObject<Banner>();
	//bn->View(Banner::ViewID::V_GameOver);
}

void TestScene::UpdateDead()
{
	readyTimer -= 1.0f / 60.0f;
	if (readyTimer <= 0.0f)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
	}
}
