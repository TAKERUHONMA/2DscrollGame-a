#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// プレイヤーキャラ
/// </summary>
class Player : public GameObject
{
public:
	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// プレイヤーの座標をセットする
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	void SetPosition(int x, int y);

	void Reset();

	int count;
	int count1;

	bool GetReversX() { return ReversX; }
	void ControlCollision();
	void SetGround(float _ground) { Ground = _ground; }
	bool MovePlayer();

	bool IsActive() { return isAlive; }//isAliveがtrueかどうか
	void DeActivateMe() { isAlive = false; }
	void ActivateMe() { isAlive = true; }

private:
	int hImage;
	int kazu;

	GameObject* sceneTop;
	bool prevSpaceKey;
	float jumpSpeed;
	bool onGround;
	int counter;
	int rcount;
	int animType; //状況
	int animFrame;//コマ
	int frameCounter;
	float transparency;//透明度
	float readyTimer;
	bool ReversX;
	int tmpPosx,tmpPosy;
	int ceiling;
	int Ground;
	bool firstGround;
	bool isAlive;

	enum State {
		S_Walk=0,
		S_Cry,
	};
	State state;
};