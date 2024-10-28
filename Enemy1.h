#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// 鳥（敵）
/// </summary>
class Enemy1 : public GameObject
{
public:
	Enemy1(GameObject* scene);
	~Enemy1();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// 鳥の座標をセットする
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	void SetPosition(int x, int y);

	//円の当たり判定をする
	bool CollideCircle(float x, float y, float r);

	void Reset();
	void ReverseEnemy();
private:
	bool prevSpaceKey;
	float jumpSpeed;
	int counter;
	bool onGround;
	float sinAngle;
	int hImage;
	float baseY;//生成時のY座標
	int animType; //状況
	int animFrame;//コマ
	int frameCounter;
	bool IsReverse;
	int tmpPosx, tmpPosy;
};
