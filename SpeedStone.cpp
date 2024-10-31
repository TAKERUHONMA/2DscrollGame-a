#include "SpeedStone.h"
#include <assert.h>
#include "Camera.h"
#include "TestScene.h"
#include "Field.h"

namespace
{
	static const int SCREEN_WIDTH = 1280;
}


SpeedStone::SpeedStone()
{
	hImage = LoadGraph("Assets/houseki.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 650.0f;
	animType = 0;
	animFrame = 0;
	frameCounter = 0;
	counter = 0;
	isAlive = true;
}

SpeedStone::SpeedStone(GameObject parent)
{
	hImage = LoadGraph("Assets/houseki.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 650.0f;
	animType = 0;
	animFrame = 0;
	frameCounter = 0;
	counter = 0;
	isAlive = true;
}

SpeedStone::~SpeedStone()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void SpeedStone::Update()
{
	counter -= 1;
	int x = (int)transform_.position_.x;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	TestScene* scene = dynamic_cast<TestScene*>(GetParent());
	if (!scene->CanMove())
		return;

	if (counter <= 0)
	{
		counter = 3;
		if (++frameCounter >= 10)
		{
			animFrame = (animFrame + 1) % 3;
			frameCounter = 0;
		}
	}

	if (x > SCREEN_WIDTH) //即値、マジックナンバー
		return;
	else if (x < 0 - 64)
	{
		KillMe();
		return;
	}

	if (transform_.position_.y >= 700)
	{
		KillMe();
	}

	if (counter == 0)
	{
		counter = 160;
	}

	if (CheckHitKey(KEY_INPUT_R))
	{
		Reset();
	}
}

void SpeedStone::Draw()
{
	if (IsAlive() == true)
	{
		int x = (int)transform_.position_.x;
		int y = (int)transform_.position_.y;
		Camera* cam = GetParent()->FindGameObject<Camera>();
		if (cam != nullptr) {
			x -= cam->GetValue();
		}

		DrawRectGraph(x, y, animFrame * 48, 48, 48, 40, hImage, TRUE, IsReverse);
	}
	else
	{

	}
}

void SpeedStone::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

bool SpeedStone::CollideCircle(float x, float y, float r)
{
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 24.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if ((dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}

void SpeedStone::Reset()
{
	KillMe();
}
