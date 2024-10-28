#pragma once
#include "Engine/GameObject.h"
class Player;
class Field;

/// <summary>
/// ƒvƒŒƒCƒ„[‚ª“Š‚°‚éÎ
/// </summary>
class Stone : public GameObject
{
public:
	Stone(GameObject* scene);
	~Stone();
	void Update() override;
	void Draw() override;
	void SetPosition(XMFLOAT3 pos);
	void Reset();
private:
	Player* pPlayer;
	Field* pField;
	int tmpPosx, tmpPosy;
	int hImage;
	int timer;
	int ceiling;
	int Ground;
	bool prevSpaceKey;
	float jumpSpeed;
	bool onGround;
	void WarpStone();
	bool IsReverse;
	float dir;
	bool colL, colR, colU, colD;
	float MoveSpeed;
	void SetMoveSpeed(float speed) { MoveSpeed = speed; }
};
