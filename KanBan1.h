#pragma once
#include "Engine/GameObject.h"
class KanBan1 :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	KanBan1(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetPosition(int x, int y);
private:
	int kanban;
};

