#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �v���C���[�L����
/// </summary>
class Player : public GameObject
{
public:
	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// �v���C���[�̍��W���Z�b�g����
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	void SetPosition(int x, int y);

	void Reset();

	bool GetReversX() { return ReversX; }
	void ControlCollision();
	void SetGround(float _ground) { Ground = _ground; }
	bool MovePlayer();

	bool IsActive() { return isAlive; }//isAlive��true���ǂ���
	void DeActivateMe() { isAlive = false; }
	void ActivateMe() { isAlive = true; }

private:
	int hImage;
	int kazu;

	GameObject* sceneTop;
	bool prevSpaceKey;
	float jumpSpeed; //�W�����v�̃X�s�[�h
	bool onGround;
	int counter; //�N�[���^�C��
	int rcount;
	int animType; //��
	int animFrame;//�R�}
	int frameCounter;
	float transparency;//�����x
	float readyTimer;
	bool ReversX;
	int tmpPosx,tmpPosy;
	int ceiling;
	int Ground;
	bool firstGround;
	bool isAlive; //����
	int count; //�A�j���[�V����
	int count1; //�X�s�[�h�X�g�[�����������

	enum State {
		S_Walk=0,
		S_Cry,
	};
	State state;
};