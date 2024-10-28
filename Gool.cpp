#include "Gool.h"
#include <assert.h>
#include "Camera.h"
#include "TestScene.h"
#include "Field.h"

namespace
{
	static const int SCREEN_WIDTH = 1280;
}

Gool::Gool(GameObject* scene)
{
	hImage = LoadGraph("Assets/hata.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 500.0f;
	counter = 0;
}

Gool::~Gool()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Gool::Update()
{

	int x = (int)transform_.position_.x;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	TestScene* scene = dynamic_cast<TestScene*>(GetParent());
	if (!scene->CanMove())
		return;

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

void Gool::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	DrawGraph(x, y, hImage, TRUE);

	//DrawCircle(x + 100.0f, y + 100.0f, 200.0f, GetColor(255, 0, 0),0);
}

void Gool::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

bool Gool::CollideCircle(float x, float y, float r)
{
	float myCenterX = transform_.position_.x + 100.0f;
	float myCenterY = transform_.position_.y + 100.0f;
	float myR = 24.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if ((dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}

void Gool::Reset()
{
	KillMe();
}
