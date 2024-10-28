#include "Stone.h"
#include <assert.h>
#include "Camera.h"
#include "Player.h"
#include "Field.h"

namespace {
	const Size S_SIZE = { 20,19 };
	const float MOVE_SPEED = 3.0f;
	const float GROUND = 400.0f;
	const float JUMP_HEIGHT = 64.0f * 2.0f;
	const float GRAVITY = 9.8f / 60.0f;
}

Stone::Stone(GameObject* scene) 
	: GameObject(scene),MoveSpeed(MOVE_SPEED)
{
	hImage = LoadGraph("Assets/stone.png");
	assert(hImage > 0);
	pPlayer = GetParent()->FindGameObject<Player>();
	IsReverse = true;
}

Stone::~Stone()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Stone::Update()
{
	tmpPosx = transform_.position_.x;
	tmpPosy = transform_.position_.y;

	pField = GetParent()->FindGameObject<Field>();

	int push = pField->CollisionRight(transform_.position_.x + 25, transform_.position_.y + 19);

	if (push > 1)
	{
		int tmp = transform_.position_.x;
		transform_.position_.x -= tmp % 32 / 10;
		colR = true;
	}
	else
	{
		colR = false;
	}

	push = pField->CollisionLeft(transform_.position_.x, transform_.position_.y + 19);

	if (push > 1)
	{
		int tmp = transform_.position_.x;
		transform_.position_.x += tmp % 32 / 10;
		colL = true;
	}
	else
	{
		colL = false;
	}

	if (pField != nullptr)
	{
		int push = pField->CollisionDown(transform_.position_.x+10, transform_.position_.y + 19);

		if (push > 1)
		{
			transform_.position_.y -= push;
			MoveSpeed = MOVE_SPEED;
			jumpSpeed = 0.0f;
			onGround = true;
			colD = true;
		}
		else
		{
			colD = false;
		}
	}

	if (onGround == false)
	{
		if (IsReverse) {
			if (pPlayer->GetReversX() == false)
			{
				dir = 1;
			}
			else if (pPlayer->GetReversX())
			{
				dir = -1;
			}
			IsReverse = false;
		}

		transform_.position_.x += MoveSpeed * dir;
		transform_.position_.y -= sqrtf(2 * GRAVITY * JUMP_HEIGHT);

		if (pField != nullptr)
		{
			int push = pField->CollisionDown(transform_.position_.x, transform_.position_.y + 19);

			if (push > 0)
			{
				transform_.position_.y += push;
				jumpSpeed = 0.0f;
				MoveSpeed = MOVE_SPEED;
				onGround = true;
				colD = true;
			}
			else
			{
				colD = false;
			}
		}
	}

	if (colL || colR || colU || colD) {
		MoveSpeed = 0;
	}

	jumpSpeed += GRAVITY;
	transform_.position_.y += jumpSpeed;


	if (--timer <= 0)
	{
		IsReverse = true;
		KillMe();
	}

	if (CheckHitKey(KEY_INPUT_R))
	{
		Reset();
	}

	WarpStone();
}

void Stone::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}
	DrawGraph(x, y, hImage, TRUE);
}

void Stone::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
	timer = 150;
}

void Stone::Reset()
{
	KillMe();
}

void Stone::WarpStone()
{
	if (timer == 2)
	{
		int pushR = pField->CollisionRight(transform_.position_.x + 80, transform_.position_.y + 19);

		if (pushR > 1)
		{
			pPlayer->SetPosition(transform_.position_.x - 40, transform_.position_.y - 65);
		}
		else
		{
			pPlayer->SetPosition(transform_.position_.x-5, transform_.position_.y - 65);
		}
	}
}