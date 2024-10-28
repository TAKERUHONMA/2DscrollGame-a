#include "KanBan1.h"
#include "Camera.h"

KanBan1::KanBan1(GameObject* parent)
{
	kanban = LoadGraph("Assets/kanban1.png");
}

void KanBan1::Initialize()
{
}

void KanBan1::Update()
{
}

void KanBan1::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) 
	{
		x -= cam->GetValue();
	}

	DrawGraph(x, y, kanban, TRUE);
}

void KanBan1::Release()
{

}

void KanBan1::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}
