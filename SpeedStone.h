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
    /// スピードストーンの座標をセットする
    /// </summary>
    /// <param name="x">X座標</param>
    /// <param name="y">Y座標</param>
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
    float baseY;//生成時のY座標
    int animType; //状況
    int animFrame;//コマ
    int frameCounter;
    bool IsReverse;
    int tmpPosx, tmpPosy;
};

