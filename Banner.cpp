#include "Banner.h"
#include <assert.h>

Banner::Banner(GameObject* scene)
	:GameObject(scene)
{
	hImage = LoadGraph("Assets/font.png");
	assert(hImage > 0);
	goY = 200;
	transparency = 0;
	overTime = 0.0f;
}

Banner::~Banner()
{
	if (hImage > 0)
		DeleteGraph(hImage);
}

#include "Ease.h"

void Banner::Update()
{
	static const float MaxTime = 1.5f;
	if (view == ViewID::V_GameOver) 
	{
		//変数を操作
		goY = GetEase<float>(200, 400,overTime / MaxTime);
		transparency = GetEase<float>(0,255,overTime / MaxTime);
		overTime += 1.0f / 60.0f;
		if (overTime > MaxTime)
			overTime = MaxTime;
	}
}

void Banner::Draw()
{
	//if (view == ViewID::V_Start)
	//	DrawRectGraph(200, 400, 0, 0, 256, 64, hImage, TRUE);//スタート
	//else if (view == ViewID::V_Clear)
	//	DrawRectGraph(200, 400, 0, 64, 256, 64, hImage, TRUE);//クリア
	//else if (view == ViewID::V_GameOver) 
	//{
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
	//	DrawRectGraph(200, goY, 0, 128, 256, 128, hImage, TRUE);//ゲームオーバー
	//}
}

void Banner::View(ViewID id)
{
	view = id;

	if (view == ViewID::V_GameOver) 
	{
		//変数の初期化
		goY = 200;
		transparency = 0;
		overTime = 0.0f;
	}
}
