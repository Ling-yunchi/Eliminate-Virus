#ifndef MONSTER_H
#define MONSTER_H


class Monster
{
public:
    Monster();
    void setPos(int x, int y);
    void move(int f);
private:
    int HP;
    int X;
    int Y;
};

#endif // MONSTER_H
