#include "monster.h"

Monster::Monster()
{

}

void Monster::setPos(int x, int y)
{
    X = x;
    Y = y;
}

void Monster::move(int f)
{
    switch (f)
    {
    case 1:
        this->setPos(X, Y - 10);
        break;
    case 2:
        this->setPos(X, Y + 10);
        break;
    case 3:
        this->setPos(X - 10, Y);
        break;
    case 4:
        this->setPos(X + 10, Y);
        break;
    default:
        break;
    }
}
