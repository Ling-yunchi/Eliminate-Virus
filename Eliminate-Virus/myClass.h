#pragma once
#include<vector>

bool Clash(int X, int Y);
bool MonsterClash(int X, int Y, int num);
struct  ActiveObject
{
    int HP;
    int X;
    int Y;
    //int speed;
    int forward = 0;
    int movetimer = 0;
    void move(int a)
    {
        switch (a)
        {
        case 1:
            Y -= 10;
            break;
        case 2:
            Y += 10;
            break;
        case 3:
            X -= 10;
            break;
        case 4:
            X += 10;
            break;
        }
    }
};

struct DestructibleWall
{
    int X;
    int Y;
    bool destroy = false;
    DestructibleWall(int X, int Y)
    {
        this->X = X;
        this->Y = Y;
    }
};

struct Boom
{
    int X;
    int Y;
    int BoomPower;
    int BoomTime;
    int DieTime;//初始为0,每一循环加一,等于500时爆炸结束
    Boom(int X, int Y, int BoomPower, int SetTime)
    {
        this->X = X;
        this->Y = Y;
        this->BoomTime = (SetTime + 500) % 10000;//爆炸时间为放置后一秒
        DieTime = 0;
        this->BoomPower = BoomPower;
    }
};

struct Player : public ActiveObject
{
    bool unbeatable = false;
    int unbeatableTime = 0;
    int BoomNumMax;
    int BoomPower;
    Player(int HP = 3, int X = 50, int Y = 50, int BoomNumMax = 1, int BoomPower = 1)//int speed;
    {
        this->HP = HP;
        this->X = X;
        this->Y = Y;
        this->BoomNumMax = BoomNumMax;
        this->BoomPower = BoomPower;
        //speed = 1;
    }
    void SetBoom(std::vector<Boom>& booms, int time)
    {
        booms.push_back(Boom(X, Y, BoomPower, time));
    }
    void Hurt()
    {
        if (unbeatable == false)
        {
            unbeatable = true;
            unbeatableTime = 1000;
            HP--;
        }
    }
    void UnbeatableTimeFresh()
    {
        if (unbeatableTime > 0)
            unbeatableTime -= 10;
        else
            unbeatable = false;
    }
};

struct Monster : public ActiveObject
{
    int num;
    Monster(int num, int HP = 1, int X = 1, int Y = 1, int forward = 0, int movetimer = 0)
    {
        this->HP = HP;
        this->X = X;
        this->Y = Y;
        //speed = 1;
        this->num = num;
        this->forward = forward;
        this->movetimer = movetimer;
    }
//    void move(int a)
//    {
//        switch (a)
//        {
//        case 1:
//            if (MonsterClash(X, Y - 1, this->num))
//                Y -= 1;
//            break;
//        case 2:
//            if (MonsterClash(X, Y + 1, this->num))
//                Y += 1;
//            break;
//        case 3:
//            if (MonsterClash(X - 1, Y, this->num))
//                X -= 1;
//            break;
//        case 4:
//            if (MonsterClash(X + 1, Y, this->num))
//                X += 1;
//            break;
//        }
//    }
};

struct Property
{
    int X;
    int Y;
    int effect;//1为增加威力,2为增加个数
    Property(int X, int Y, int effect)
    {
        this->X = X;
        this->Y = Y;
        this->effect = effect;
    }
};

