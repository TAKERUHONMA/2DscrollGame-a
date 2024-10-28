#pragma once
#include "Engine/GameObject.h"

//テストシーンを管理するクラス
class TestScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TestScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	bool CanMove();
private:
	enum State {
	    S_Ready, //Ready表示中(2秒間すたーとを表示)
	    S_Play, //ゲーム中
		S_Clear, //ゲームクリア(クリアを表示してボタンが押されるまで待つ)
		S_Dead, //死亡(ゲームオーバーを表示してボタンが押されるまで待つ)
	};
	State state; //ステートの値を保持
	float readyTimer;
	void StartReady();
	void UpdateReady();
	void StartPlay();
	void UpdatePlay();
	void StartClear();
	void UpdateClear();
public:
	void StartDead();
private:
	void UpdateDead();
};