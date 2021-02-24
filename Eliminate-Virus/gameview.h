#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QIcon>
#include <QPainter>
#include <QBrush>
#include <QTimer>
#include <QString>
#include <QKeyEvent>
#include <QPushButton>
#include <list>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <list>
#include <vector>
#include <Windows.h>
#include <time.h>
#include "myclass.h"


using namespace std;

class gameover;
class GameView : public QWidget
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);
    explicit GameView(QString level);
private:
    Player player;
    //QPainter* painter;
    QPushButton* pausebtn;
    list<Monster> monsters;
    list<DestructibleWall> dWalls;
    list<Property> properties;
    vector<Boom> booms;
    gameover *o;
    QTimer *timer;
    QString Level;
    char map[17][17];

    void startUp();
    void setMapAndMusic(QString);
    //void playMusic();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void updataWithInpute(Player& player);
    void updataWithoutInput();
    void failure();
    void win();
    int randEx();
    bool Clash(int X, int Y);//运动物体与非运动物体的碰撞
    bool MonsterClash(int X, int Y, int num);//怪物之间的碰撞
    bool knocked(int, int, int, int);//运动物体之间的碰撞
    void pause();
    void propertydrop(int, int);

public slots:
    void advance();
    void pauseclick();

signals:

};

#endif // GAMEVIEW_H
