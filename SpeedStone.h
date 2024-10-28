#pragma once
#include "Engine/GameObject.h"
class SpeedStone :
    public GameObject
{
public:
    SpeedStone(GameObject parent);
    ~SpeedStone();
    void Update() override;
    void Draw() override;

    /// <summary>
    /// �X�s�[�h�X�g�[���̍��W���Z�b�g����
    /// </summary>
    /// <param name="x">X���W</param>
    /// <param name="y">Y���W</param>
    void SetPosition(int x, int y);


    bool CollideCircle(float x, float y, float r);

    void Reset();
private:
    bool prevSpaceKey;
    float jumpSpeed;
    int counter;
    bool onGround;
    float sinAngle;
    int hImage;
    float baseY;//��������Y���W
    int animType; //��
    int animFrame;//�R�}
    int frameCounter;
    bool IsReverse;
    int tmpPosx, tmpPosy;
};

