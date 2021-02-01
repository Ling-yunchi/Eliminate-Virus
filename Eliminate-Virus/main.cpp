#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<conio.h>
#include<list>
#include<vector>
#include<Windows.h>
#include<time.h>
#include"myClass.h"

using namespace std;
void gotoxy(short x, short y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//void loadPicture();
void startUp();
//void dataMap();
//void playMusic();
void show(Player& player, list<Monster>& monsters, vector<Boom>& booms);
void updataWithInpute(Player& player);
void updataWithoutInput();
void failure();
int randEx();
extern char map[17][17] = {
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
	{'#','@',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ','#'},
	{'#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ','#',' ','#',' ','#',' ','#','*','#',' ','#',' ','#',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
	{'#',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ','*','#'},
	{'#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ','#'},
	{'#','*','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
	{'#',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ','#'},
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
};
Player player;
list<Monster> monsters;
vector<Boom> booms;
int cntTime = 0;//单位毫秒
const int TIMELIMIT = 10000;
int main()
{
	int cnt = 0;
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			if (map[i][j] == '@')
			{
				player.X = i;
				player.Y = j;
			}
			if (map[i][j] == '*')
			{
				monsters.push_back(Monster(cnt, 1, i, j));
				cnt++;
			}
		}
	}

	startUp();

	while (1)
	{
		cntTime+=10;
		cntTime %= TIMELIMIT;//time上限为10秒
		updataWithInpute(player);
		updataWithoutInput();
		show(player, monsters, booms);
		if (monsters.empty())
			break;
		if (player.HP <= 0)
			failure();
		Sleep(10);
	}
	system("cls");
	printf("YOU WIN!!!");
	return 0;
}
void show(Player& player, list<Monster>& monsters, vector<Boom>& booms) {
	gotoxy(0, 0);
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			if (map[i][j] == '#')
				printf("%c", '#');
			else
				printf(" ");
		}
		printf("\n");
	}

	for (int i = 0; i < (int)booms.size(); i++)
	{
		if (booms[i].BoomTime == cntTime || (booms[i].DieTime && booms[i].DieTime <= 1000))
		{
			int X = booms[i].X, Y = booms[i].Y;
			gotoxy(X, Y);
			printf("^");
			for (int j = 1; j <= booms[i].BoomPower; j++)
			{
				if (map[X + j][Y] == '#')
					break;
				gotoxy(X + j, Y);
				printf("^");
			}
			for (int j = 1; j <= booms[i].BoomPower; j++)
			{
				if (map[X - j][Y] == '#')
					break;
				gotoxy(X - j, Y);
				printf("^");
			}
			for (int j = 1; j <= booms[i].BoomPower; j++)
			{
				if (map[X][Y + j] == '#')
					break;
				gotoxy(X, Y + j);
				printf("^");
			}
			for (int j = 1; j <= booms[i].BoomPower; j++)
			{
				if (map[X][Y - j] == '#')
					break;
				gotoxy(X, Y - j);
				printf("^");
			}
		}
		else
		{
			gotoxy(booms[i].X, booms[i].Y);
			printf("&");

		}
	}

	gotoxy(player.X, player.Y);
	printf("@");

	for (auto it = monsters.begin(); it != monsters.end(); it++)
	{
		gotoxy(it->X, it->Y);
		printf("*");
	}
	gotoxy(0, 17);
	int boomCnt = player.BoomNumMax - booms.size();
	cout << "可放置的炸弹数: " << boomCnt;
	gotoxy(0, 18);
	cout << "炸弹威力: " << player.BoomPower;
	gotoxy(0, 19);
	printf("HP:%d\n", player.HP);
	if (player.unbeatable)
		printf("unbeatable!");
	else
		printf("           ");
}
void updataWithInpute(Player& player)
{
	if (_kbhit())
	{
		int input = _getch();
		//printf("%d", input);
		switch (input)
		{
		case 224:
			input = _getch();
			switch (input)
			{
			case 72:
				player.move(1); break;
			case 80:
				player.move(2); break;
			case 75:
				player.move(3); break;
			case 77:
				player.move(4); break;
			}
			break;
		case 32:
			if(booms.size()<player.BoomNumMax)
			player.Boom(booms, cntTime); break;
		case 27:
			gotoxy(0, 17);
			system("pause");
		}
	}
}
void updataWithoutInput()
{
	//炸弹的处理
	for (int i = 0; i < (int)booms.size(); i++)
	{
		if (booms[i].BoomTime == cntTime || (booms[i].DieTime && booms[i].DieTime <= 1000))
		{
			for (int j = booms[i].X - booms[i].BoomPower; j <= booms[i].X + booms[i].BoomPower; j++)
			{
				if (player.X == j && player.Y == booms[i].Y)
					player.Hurt();

				for (auto it = monsters.begin(); it != monsters.end(); it++)
					if (it->X == j && it->Y == booms[i].Y)
						it->HP--;
			}
			for (int j = booms[i].Y - booms[i].BoomPower; j <= booms[i].Y + booms[i].BoomPower; j++)
			{
				if (player.Y == j && player.X == booms[i].X)
					player.Hurt();

				for (auto it = monsters.begin(); it != monsters.end(); it++)
					if (it->Y == j && it->X == booms[i].X)
						it->HP--;
			}
			booms[i].DieTime+=10;
		}
		if (booms[i].DieTime > 1000)
		{
			booms.erase(booms.begin() + i);
		}
	}
	//怪物的处理
	auto it = monsters.begin();
	while (it != monsters.end())
	{
		if (it->HP <= 0)
			it = monsters.erase(it);
		else
			it++;
	}

	if (cntTime % 1000 == 0)//一秒走一次
	{
		//gotoxy(0, 19);
		//cout << "运动!";
		for (auto it = monsters.begin(); it != monsters.end(); it++)
		{
			int move = randEx()%5;
			switch (move)
			{
			case 1:
				it->move(1); break;
			case 2:
				it->move(2); break;
			case 3:
				it->move(3); break;
			case 4:
				it->move(4); break;
			}
			move += 7;
		}
	}
	//玩家的处理
	player.UnbeatableTimeFresh();
	for (auto it = monsters.begin(); it != monsters.end(); it++) {
		if (player.X == it->X && player.Y == it->Y)
			player.Hurt();
	}
}

void failure() {
	system("cls");
	cout << "YOU FAILED!!";
	exit(0);
}

bool Clash(int X, int Y) {
	if (map[X][Y] == '#')
		return false;
	for (int i = 0; i < (int)booms.size(); i++)
		if (X == booms[i].X && Y == booms[i].Y)
			return false;
	return true;
}

bool MonsterClash(int X, int Y,int num)
{
	if (Clash(X, Y))
	{
		for (auto it = monsters.begin(); it != monsters.end(); it++)
		{
			if (it->num == num)
				continue;
			if (it->X == X && it->Y == Y)
				return false;
		}
		return true;
	}
	else
		return false;
}

int randEx()
{
	LARGE_INTEGER seed;
	QueryPerformanceFrequency(&seed);
	QueryPerformanceCounter(&seed);
	srand(seed.QuadPart);

	return rand();
}

void startUp() {
	cout << "上下左右控制,空格键放炸弹\n杀死所有敌人后胜利,血量降为零失败qwqq" << endl;
	system("pause");
	system("cls");
}