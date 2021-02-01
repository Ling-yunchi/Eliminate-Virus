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
	void move(int a) {
		switch (a) {
		case 1:
			if (Clash(X, Y - 1))
				Y -= 1; break;
		case 2:
			if (Clash(X, Y + 1))
				Y += 1; break;
		case 3:
			if (Clash(X - 1, Y))
				X -= 1; break;
		case 4:
			if (Clash(X + 1, Y))
				X += 1; break;
		}
	}
};

struct Boom {
	int X;
	int Y;
	int BoomPower;
	int BoomTime;
	int DieTime;//初始为0,每一循环加一,等于1000时爆炸结束
	Boom(int X, int Y, int BoomPower, int SetTime)
	{
		this->X = X;
		this->Y = Y;
		this->BoomTime = SetTime + 1000;//爆炸时间为放置后一秒
		DieTime = 0;
		this->BoomPower = BoomPower;
	}
};

struct Player :public ActiveObject
{
	bool unbeatable = false;
	int unbeatableTime = 0;
	int BoomNumMax;
	int BoomPower;
	Player(int HP = 3, int X = 1, int Y = 1, int BoomNumMax = 3 , int BoomPower = 3)//int speed;
	{
		this->HP = HP;
		this->X = X;
		this->Y = Y;
		this->BoomNumMax = BoomNumMax;
		this->BoomPower = BoomPower;
		//speed = 1;
	}
	void Boom(std::vector<Boom>& booms, int time) {
		booms.push_back(Boom::Boom(X, Y, BoomPower, time));
	}
	void Hurt() {
		if (unbeatable == false)
		{
			unbeatable = true;
			unbeatableTime = 1000;
			HP--;
		}
	}
	void UnbeatableTimeFresh() {
		if (unbeatableTime > 0)
			unbeatableTime -= 10;
		else
			unbeatable = false;
	}
};

struct Monster :public ActiveObject
{
	int num;
	Monster(int num,int HP = 1, int X = 1, int Y = 1)
	{
		this->HP = HP;
		this->X = X;
		this->Y = Y;
		//speed = 1;
		this->num = num;
	}
	void move(int a)
	{
		switch (a) {
		case 1:
			if (MonsterClash(X, Y - 1, this->num))
				Y -= 1; break;
		case 2:
			if (MonsterClash(X, Y + 1, this->num))
				Y += 1; break;
		case 3:
			if (MonsterClash(X - 1, Y, this->num))
				X -= 1; break;
		case 4:
			if (MonsterClash(X + 1, Y, this->num))
				X += 1; break;
		}
	}
};

