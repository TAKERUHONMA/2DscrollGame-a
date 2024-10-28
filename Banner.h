#pragma once
#include "Engine/GameObject.h"

class Banner :public GameObject
{
public:
	Banner(GameObject* scene);
	~Banner();
	void Update() override;
	void Draw() override;
	enum ViewID {
		V_Start = 0,
		V_Clear,
		V_GameOver,
		V_Nothing,
	};
	void View(ViewID id);
private:
	int hImage;
	ViewID view;
	//ゲームオーバー表示用
	float transparency;//透明度
	float goY;//ゲームオーバーの字のY座標
	float overTime;
};
