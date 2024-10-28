#include "Field.h"
#include <assert.h>
#include "Camera.h"
#include "Player.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Gool.h"
#include "KanBan1.h"
#include "Stone.h"
#include "SpeedStone.h"
#include "Engine/CsvReader.h"



Field::Field(GameObject* scene)
	:GameObject(scene)
{
	hImage = LoadGraph("Assets/bgchar.png");
	background = LoadGraph("Assets/mori.jpg");
	stone = LoadGraph("Assets/isi.png");
	sousa = LoadGraph("Assets/sousa.png");
	assert(hImage > 0);
	assert(background > 0);
	Map = nullptr;
}

Field::~Field()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
	if (Map != nullptr) {
		delete[] Map; //Mapは配列
	}
}

void Field::Reset()
{
	if (Map != nullptr) {
		delete[] Map;
		Map = nullptr;
	}
	CsvReader csv;//データを読むクラスfのインスタンスを作成
	bool ret = csv.Load("Assets/stage1.csv");
	assert(ret);
	width = csv.GetWidth(0);
	height = csv.GetHeight();
	Map = new int[width * height];//C言語での動的二次元配列の取り方
	
	for (int h = 0; h < height; h++) 
	{
		if (csv.GetString(0, h) == "") 
		{
			height = h;
			break;
		}
		for (int w = 0; w < width; w++)
		{
			Map[h*width+w] = csv.GetInt(w, h);
		}
	}
	//Mapデータの中で0があれば、Playerの座標を0の位置にする
	for (int h = 0; h < height; h++) 
	{
		for (int w = 0; w < width; w++) 
		{
			switch (csv.GetInt(w,h+height+1))
			{
			case 0://player
			{
				Player* pplayer = GetParent()->FindGameObject<Player>();
				pplayer->SetPosition(w * 32, h * 32);
				pplayer->SetGround((h * 32) - 20);
			}
			break;
			case 1://bird
			{
				Enemy1* pEne1 = Instantiate<Enemy1>(GetParent());
				pEne1->SetPosition(w * 32, h * 32);
			}
			break;
			case 2://Livingthings
			{
				Enemy2* pEne2 = Instantiate<Enemy2>(GetParent());
				pEne2->SetPosition(w * 32, h * 32);
			}
			break;
			case 3://Gool
			{
				Gool* Gools = Instantiate<Gool>(GetParent());
				Gools->SetPosition(w * 32, h * 32);
			}
			break;
			case 4://SpeedStone
			{
				SpeedStone* Ss = Instantiate<SpeedStone>(GetParent());
				Ss->SetPosition(w * 32, h * 32);
			}
			break;
			}
		}
	}
}

void Field::Update()
{
	if (CheckHitKey(KEY_INPUT_R))
		Reset();
}

void Field::Draw()
{
	DrawGraph(0,0, background, TRUE);

	DrawGraph(0, 0, stone, TRUE);

	DrawGraph(0, 50, sousa, TRUE);

	scroll = 0;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) 
	{
		scroll = cam->GetValue();
	}

	IsScroll();

	for (int y = 0; y < height; y++) 
	{
		for (int x = 0; x < width; x++) 
		{
			int chip = Map[y*width+x];
			DrawRectGraph(x*32-scroll, y*32, 32 * (chip % 16), 32 * (chip / 16), 32, 32, hImage, TRUE);
		}
	}
}

int Field::CollisionRight(int x, int y)
{
	if (IsWallBlock(x, y))
	{
		//当たっているので、めり込んだ量を返す
		return x % 32 + 1;
	}
	else
		return 0;
}

int Field::CollisionLeft(int x, int y)
{
	if (IsWallBlock(x, y)) 
	{
		//当たっているので、めり込んだ量を返す
		return x % 32 - 1;
	}
	else
		return 0;
}

int Field::CollisionDown(int x, int y)
{
	if (IsWallBlock(x, y)) 
	{
		//当たっているので、めり込んだ量を返す
		return y % 32 + 1;
	}
	else
		return 0;
}

int Field::CollisionUp(int x, int y)
{
	if (IsWallBlock(x, y)) 
	{
		//当たっているので、めり込んだ量を返す
		return y % 32 + 1;
	}
	else
		return 0;
}

void Field::IsScroll()
{
	if (scroll <= 0) {
		scroll = 0;
		LeftSc = false;
	}
	else {
		LeftSc = true;
	}

	if (scroll >= width * 32 - WIN_WIDTH) {
		scroll = width * 32 - WIN_WIDTH;
		RightSc = false;
	}
	else {
		RightSc = true;
	}
}

bool Field::IsCollisionRight(int i)
{
	Player* pPlayer = GetParent()->FindGameObject<Player>();
	int Nx = pPlayer->GetPosition().x / 32;
	int Ny = (pPlayer->GetPosition().y + i) / 32;
	switch (Map[Ny * width + Nx + 2]) {
	case 16:
	case 17:
	case 18:
	case 19:
	case 32:
	case 33:
	case 34:
	case 35:
		return true;
	}
	return false;
}

bool Field::IsCollisionLeft(int i)
{
	Player* pPlayer = GetParent()->FindGameObject<Player>();
	int Nx = pPlayer->GetPosition().x / 32;
	int Ny = (pPlayer->GetPosition().y + i) / 32;
	switch (Map[Ny * width + Nx]) {
	case 16:
	case 17:
	case 18:
	case 19:
	case 32:
	case 33:
	case 34:
	case 35:
		return true;
	}
	return false;
}

bool Field::IsCollisionUp(int i)
{
	Player* pPlayer = GetParent()->FindGameObject<Player>();
	int Nx = (pPlayer->GetPosition().x + i) / 32;
	int Ny = pPlayer->GetPosition().y / 32;
	switch (Map[Ny * width + Nx]) {
	case 16:
	case 17:
	case 18:
	case 19:
	case 32:
	case 33:
	case 34:
	case 35:
		return true;
	}
	return false;
}

bool Field::IsCollisionDown(int i)
{
	Player* pPlayer = GetParent()->FindGameObject<Player>();
	int Nx = (pPlayer->GetPosition().x + i) / 32;
	int Ny = (pPlayer->GetPosition().y + 88) / 32;
	switch (Map[Ny * width + Nx]) {
	case 16:
	case 17:
	case 18:
	case 19:
	case 32:
	case 33:
	case 34:
	case 35:
		return true;
	}
	return false;
}

bool Field::EnemyCollisionRight(int i)
{
	Enemy1* en1 = GetParent()->FindGameObject<Enemy1>();
	int Nx = en1->GetPosition().x / 32;
	int Ny = (en1->GetPosition().y + i) / 32;
	switch (Map[Ny * width + Nx + 2]) {
	case 16:
	case 17:
	case 18:
	case 19:
	case 32:
	case 33:
	case 34:
	case 35:
		return true;
	}
	return false;
}

bool Field::EnemyCollisionLeft(int i)
{
	Enemy1* en1 = GetParent()->FindGameObject<Enemy1>();
	int Nx = en1->GetPosition().x / 32;
	int Ny = (en1->GetPosition().y + i) / 32;
	switch (Map[Ny * width + Nx]) {
	case 16:
	case 17:
	case 18:
	case 19:
	case 32:
	case 33:
	case 34:
	case 35:
		return true;
	}
	return false;
}


bool Field::IsWallBlock(int x, int y)
{
	int chipX = x / 32;
	int chipY = y / 32;
	switch (Map[chipY*width+chipX]) 
	{
	case 16:
	case 17:
	case 18:
	case 19:
	case 32:
	case 33:
	case 34:
	case 35:
		return true;
	}
	return false;
}
