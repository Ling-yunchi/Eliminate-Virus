#include "gameview.h"
#include <QDebug>
#include "gameover.h"

using namespace std;



//地图存储
//#为不可破坏墙,&为可破坏墙,@为人物初始位置,*为怪物初始位置qwqq

char map1_1[17][17] =
{
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '&', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '&', '*', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

char map1_2[17][17] =
{
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', '&', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
    {'#', '&', '#', ' ', '&', ' ', '#', ' ', ' ', '*', ' ', ' ', '#', ' ', ' ', ' ', '#'},
    {'#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
    {'#', ' ', '&', '*', '&', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '*', '#'},
    {'#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '&', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', '*', ' ', ' ', '&', ' ', '#'},
    {'#', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', '*', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#'},
    {'#', ' ', '#', ' ', '&', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#'},
    {'#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '*', '#', ' ', '#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', '#', ' ', '#', '#', '#', '&', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', '#', ' ', ' ', ' ', '*', ' ', '&', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}

};

char map1_3[17][17] =
{
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '@', ' ', '&', '#', '#', '&', '*', '&', '&', ' ', ' ', '#', '#', '#', '#', '#'},
    {'#', ' ', '&', '&', '#', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', '#'},
    {'#', '#', '&', '#', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#', '#'},
    {'#', '#', '&', '&', '&', '&', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', '#'},
    {'#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#'},
    {'#', '#', ' ', ' ', ' ', '#', '*', '#', ' ', ' ', '#', '&', '&', '#', '#', '#', '#'},
    {'#', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', '#', '&', '#', ' ', ' ', '#', '&', '#'},
    {'#', '&', '&', '&', ' ', '#', ' ', '#', '#', '#', ' ', ' ', ' ', '#', '#', ' ', '#'},
    {'#', '&', '#', '#', '&', '#', '&', '#', '#', '#', '#', '&', '&', '&', '&', '&', '#'},
    {'#', ' ', ' ', ' ', '*', ' ', ' ', ' ', '*', ' ', '#', '#', ' ', '#', ' ', ' ', '#'},
    {'#', '&', '#', '&', '&', '#', '&', '#', '#', '&', '#', '#', '&', '#', '#', '&', '#'},
    {'#', '&', '#', '#', ' ', '#', '&', '#', ' ', ' ', ' ', '#', '*', ' ', '#', ' ', '#'},
    {'#', '&', '&', '#', ' ', '#', '*', ' ', ' ', '#', '&', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', '#', ' ', '*', ' ', ' ', ' ', '#', ' ', '#', '#', '#', ' ', ' ', '#', ' ', '#'},
    {'#', '#', '#', '#', '&', '#', '#', '#', '&', '*', '&', '&', '#', '#', '#', '&', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

char map1_4[17][17] =
{
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '@', ' ', '&', '&', '&', '#', '#', ' ', ' ', ' ', ' ', ' ', '&', '&', '&', '#'},
    {'#', ' ', ' ', ' ', '#', '#', '#', '#', '&', '&', '#', ' ', ' ', ' ', ' ', '&', '#'},
    {'#', '&', '&', '#', '#', '&', '&', '&', ' ', ' ', ' ', '#', '#', ' ', ' ', '&', '#'},
    {'#', '&', ' ', ' ', '*', ' ', '#', '#', '#', '#', '&', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', '#', '#', ' ', ' ', ' ', ' ', ' ', '&', '&', '&', '&', '#', '&', '&', '&', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '&', '#', '#', '#', ' ', ' ', ' ', ' ', '&', '#'},
    {'#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '&', '&', '&', '#', '#', '&', '&', '#'},
    {'#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '&', ' ', ' ', '&', '#', '#'},
    {'#', '#', ' ', '*', ' ', ' ', '*', ' ', ' ', '&', '&', ' ', ' ', ' ', '&', '#', '#'},
    {'#', '&', '&', '&', '#', '#', '&', '&', '&', ' ', ' ', ' ', ' ', '#', '#', '#', '#'},
    {'#', ' ', ' ', '#', '#', '#', '&', '&', '#', '#', '#', ' ', ' ', ' ', '#', '#', '#'},
    {'#', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '&', '&', '#', '#'},
    {'#', ' ', ' ', '#', '&', '#', '#', '&', ' ', ' ', ' ', '&', '#', ' ', ' ', ' ', '#'},
    {'#', '&', '&', '&', '#', '#', '#', ' ', ' ', '#', '&', '#', ' ', ' ', ' ', '&', '#'},
    {'#', '#', '#', '#', '*', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', '*', ' ', '#', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

char map1_5[17][17] =
{
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '&', '#', '&', '#', '&', '#', '&', '#', ' ', '#', '&', '&', '#', '&', '&', '#'},
    {'#', '*', '&', '&', '&', ' ', '*', '&', '&', '&', '&', '&', '&', '#', '#', '&', '#'},
    {'#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '&', '#', '*', '#', '*', '&', '#'},
    {'#', '#', ' ', '&', ' ', ' ', '&', ' ', '#', '&', '&', '&', ' ', ' ', ' ', '&', '#'},
    {'#', '&', '&', '#', '&', '#', ' ', '&', ' ', ' ', '#', ' ', '#', '*', '#', '&', '#'},
    {'#', '#', ' ', '&', ' ', ' ', ' ', '#', '#', '#', '*', '&', ' ', ' ', '#', '#', '#'},
    {'#', ' ', '#', '#', '*', '#', '&', '#', '#', '&', ' ', '&', '#', '&', '&', '&', '#'},
    {'#', '&', ' ', ' ', '&', '#', '&', '@', '&', '&', '#', '&', '&', '*', '#', '&', '#'},
    {'#', '&', '&', '#', '&', '#', '*', '#', '&', '#', ' ', ' ', '#', '&', '#', '#', '#'},
    {'#', '#', '&', ' ', '&', '&', '&', '#', '&', ' ', '&', '&', '#', '&', '&', '&', '#'},
    {'#', '&', ' ', '#', ' ', ' ', '&', '*', '&', ' ', '#', ' ', '#', '*', ' ', '&', '#'},
    {'#', '#', '&', ' ', '*', '#', ' ', '#', '#', '&', '#', '&', ' ', ' ', '#', '&', '#'},
    {'#', '#', '&', '&', ' ', '#', '&', '&', '&', ' ', '*', ' ', '#', '&', '#', '#', '#'},
    {'#', '&', '&', '&', '&', ' ', ' ', '#', '&', '#', ' ', '&', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', '*', ' ', '#', '#', '&', '&', '&', '#', '&', '&', '#', '&', '&', '&', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

char map1_6[17][17] =
{
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '#'},
    {'#', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '#'},
    {'#', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '#'},
    {'#', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '#'},
    {'#', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '#'},
    {'#', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '#'},
    {'#', '*', '*', '*', '*', '*', '*', '&', '&', '&', '*', '*', '*', '*', '*', '*', '#'},
    {'#', '*', '&', '*', '&', '*', '&', '&', '@', '&', '&', '*', '&', '*', '&', '*', '#'},
    {'#', '*', '*', '*', '*', '*', '*', '&', '&', '&', '*', '*', '*', '*', '*', '*', '#'},
    {'#', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '#'},
    {'#', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '#'},
    {'#', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '#'},
    {'#', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '#'},
    {'#', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '&', '*', '#'},
    {'#', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};
extern const int TIMELIMIT = 10000;
int cntTime = 0;//单位毫秒

GameView::GameView(QString level)
{

    setFixedSize(1050, 850);
    //qDebug() << this->size();
    setWindowTitle("Eliminate-Virus");
    setWindowIcon(QIcon("../src/icon.ico"));
    setAutoFillBackground(true);

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QBrush(QPixmap("../src/bg.jpg").scaled(width(), height()))));
    this->setPalette(palette);

    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    pausebtn = new QPushButton("暂停", this);
    pausebtn->move(900, 800);
    connect(pausebtn, &QPushButton::clicked, this, &GameView::pauseclick);

    //painter = nullptr;

    qDebug() << level;

    Level = level;

    setMapAndMusic(Level);

    mciSendString(TEXT("open ../src/boooom.wav alias boom"), NULL, 0, NULL);
    mciSendString(TEXT("play bgm from 0"), NULL, 0, NULL);

    int cnt = 0;
    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (map[i][j] == '@')
            {
                player.X = i * 50;
                player.Y = j * 50;
            }
            if (map[i][j] == '*')
            {
                monsters.push_back(Monster(cnt, 1, i * 50, j * 50, randEx() % 5, randEx() % 15 + 6));
                cnt++;
            }
            if(map[i][j] == '&')
            {
                dWalls.push_back(DestructibleWall(i * 50, j * 50));
            }
        }
    }

    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &GameView::advance);
    timer->start(20);
}

void GameView::setMapAndMusic(QString Level)
{
    if(Level == QString("1-1"))
    {
        mciSendString(TEXT("open ../src/1-1.wav alias bgm"), NULL, 0, NULL);
        for(int i = 0; i < 17; i++)
            for(int j = 0; j < 17; j++)
                map[i][j] = map1_1[i][j];
    }

    if(Level == QString("1-2"))
    {
        mciSendString(TEXT("open ../src/1-2.wav alias bgm"), NULL, 0, NULL);
        for(int i = 0; i < 17; i++)
            for(int j = 0; j < 17; j++)
                map[i][j] = map1_2[i][j];
    }
    if(Level == QString("1-3"))
    {
        mciSendString(TEXT("open ../src/1-3.wav alias bgm"), NULL, 0, NULL);
        for(int i = 0; i < 17; i++)
            for(int j = 0; j < 17; j++)
                map[i][j] = map1_3[i][j];
    }
    if(Level == QString("1-4"))
    {
        mciSendString(TEXT("open ../src/1-4.wav alias bgm"), NULL, 0, NULL);
        for(int i = 0; i < 17; i++)
            for(int j = 0; j < 17; j++)
                map[i][j] = map1_4[i][j];
    }
    if(Level == QString("1-5"))
    {
        mciSendString(TEXT("open ../src/1-5.wav alias bgm"), NULL, 0, NULL);
        for(int i = 0; i < 17; i++)
            for(int j = 0; j < 17; j++)
                map[i][j] = map1_5[i][j];
    }
    if(Level == QString("1-6"))
    {
        mciSendString(TEXT("open ../src/1-6.wav alias bgm"), NULL, 0, NULL);
        for(int i = 0; i < 17; i++)
            for(int j = 0; j < 17; j++)
                map[i][j] = map1_6[i][j];
    }
}

void GameView::advance()
{
    cntTime += 10;
    cntTime %= TIMELIMIT;//time上限为10秒
    updataWithoutInput();
    update();
    if (monsters.empty())
        win();
    if (player.HP <= 0)
        failure();
}

void GameView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QFont font("Microsoft YaHei", 15, 75);
    painter.setFont(font);

    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (map[i][j] == '#')
                painter.drawPixmap(i * 50, j * 50, 50, 50, QPixmap("../src/Indestructible-wall.png"));
        }
    }

    for(auto it = dWalls.begin(); it != dWalls.end(); it++)
    {
        painter.drawPixmap(it->X, it->Y, 50, 50, QPixmap("../src/Destructible-wall.png"));
    }

    for (int i = 0; i < (int)booms.size(); i++)
    {
        if (booms[i].BoomTime == cntTime || (booms[i].DieTime && booms[i].DieTime <= 500))
        {
            int X = booms[i].X, Y = booms[i].Y;
            painter.drawPixmap(X, Y, 50, 50, QPixmap("../src/Boooom.png"));
            for (int j = 1; j <= booms[i].BoomPower; j++)
            {
                if (map[X / 50 + j][Y / 50] == '#')
                    break;
                painter.drawPixmap(X + j * 50, Y, 50, 50, QPixmap("../src/Boooom.png"));
//                gotoxy(X + j, Y);
//                printf("^");
            }
            for (int j = 1; j <= booms[i].BoomPower; j++)
            {
                if (map[X / 50 - j][Y / 50] == '#')
                    break;
                painter.drawPixmap(X - j * 50, Y, 50, 50, QPixmap("../src/Boooom.png"));
//                gotoxy(X - j, Y);
//                printf("^");
            }
            for (int j = 1; j <= booms[i].BoomPower; j++)
            {
                if (map[X / 50][Y / 50 + j] == '#')
                    break;
                painter.drawPixmap(X, Y + j * 50, 50, 50, QPixmap("../src/Boooom.png"));
//                gotoxy(X, Y + j);
//                printf("^");
            }
            for (int j = 1; j <= booms[i].BoomPower; j++)
            {
                if (map[X / 50][Y / 50 - j] == '#')
                    break;
                painter.drawPixmap(X, Y - j * 50, 50, 50, QPixmap("../src/Boooom.png"));
//                gotoxy(X, Y - j);
//                printf("^");
            }
        }
        else
        {
            painter.drawPixmap(booms[i].X, booms[i].Y, 50, 50, QPixmap("../src/Boom.png"));
//            gotoxy(booms[i].X, booms[i].Y);
//            printf("&");

        }
    }

    for(auto it = properties.begin(); it != properties.end(); it++)
    {
        if(it->effect == 1)
            painter.drawPixmap(it->X, it->Y, 50, 50, QPixmap("../src/weili.png"));
        if(it->effect == 2)
            painter.drawPixmap(it->X, it->Y, 50, 50, QPixmap("../src/shu.png"));
    }

    painter.drawPixmap(player.X, player.Y, 50, 50, QPixmap("../src/me_1.png"));

    for (auto it = monsters.begin(); it != monsters.end(); it++)
        painter.drawPixmap(it->X, it->Y, 50, 50, QPixmap("../src/monster_1.png"));

    char Text[30];

    sprintf(Text, "HP: %d", player.HP);
    painter.drawText(870, 50, Text);

    int boomCnt = player.BoomNumMax - booms.size();
    sprintf(Text, "可放置的炸弹数: %d", boomCnt);
    painter.drawText(870, 100, Text);

    sprintf(Text, "炸弹威力: %d", player.BoomPower);
    painter.drawText(870, 150, Text);

    painter.drawText(870, 200, "关卡:" + Level);

    if(Level == "1-1")
    {
        painter.drawText(870, 250, "虽然我在开始界面");
        painter.drawText(870, 300, "放了个帮助,但是");
        painter.drawText(870, 350, "你根本没看对吧");
        painter.drawText(870, 400, "￣へ￣");
        painter.drawText(870, 450, "我大发慈悲再说一遍");
        painter.drawText(870, 500, "上下左右控制方向");
        painter.drawText(870, 550, "空格放炸弹,esc暂停");
        painter.drawText(870, 600, "就酱(￣﹃￣)");
    }
    else if(Level == "1-2")
    {
        painter.drawText(870, 250, "相信你已经学会了");
        painter.drawText(870, 300, "正确的玩法");
        painter.drawText(870, 350, "那么加油取得胜利吧!");
        painter.drawText(870, 400, "（<ゝω·）诶嘿~☆");
    }
    else if(Level == "1-6")
    {
        painter.drawText(870, 250, "开 幕 雷 击");
        painter.drawText(870, 300, "都说了前面是地狱了");
        painter.drawText(870, 350, "那么加油取得胜利吧!");
        painter.drawText(870, 400, "（<ゝω·）诶嘿~☆");
    }
    else
    {
        painter.drawText(860, 750, "（<ゝω·）诶嘿嘿~☆");
    }


    //painter.setp

//    if (player.unbeatable)
//        printf("unbeatable!");
//    else
//        printf("           ");
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->key();
    qDebug() << player.forward;
    if(player.forward == 0) //没方向才接受键盘操作
    {
        switch (event->key())
        {
        case Qt::Key_Up:
            qDebug() << "up";
            if (Clash(player.X / 50, player.Y / 50 - 1))
                player.forward = 1;
            break;
        case Qt::Key_Down:
            qDebug() << "down";
            if (Clash(player.X / 50, player.Y / 50 + 1))
                player.forward = 2;
            break;
        case Qt::Key_Left:
            qDebug() << "left";
            if (Clash(player.X / 50 - 1, player.Y / 50))
                player.forward = 3;
            break;
        case Qt::Key_Right:
            qDebug() << "right";
            if (Clash(player.X / 50 + 1, player.Y / 50))
                player.forward = 4;
            break;
        case Qt::Key_Space:
            qDebug() << "boom";
            if ((int)booms.size() < player.BoomNumMax)
                player.SetBoom(booms, cntTime);
            break;
        case Qt::Key_Question:
            for (auto it = monsters.begin(); it != monsters.end(); it++)
                it->HP = 0;
            break;
        case Qt::Key_Escape:
            pause();
            break;
        }
    }
}
//void GameView::updataWithInpute(Player& player)
//{
//    if (_kbhit())
//    {
//        int input = _getch();
//        //printf("%d", input);
//        switch (input)
//        {
//        case 47:
//            win();
//            exit(0);
//        case 224:
//            input = _getch();
//            switch (input)
//            {
//            case 72:
//                player.move(1);
//                break;
//            case 80:
//                player.move(2);
//                break;
//            case 75:
//                player.move(3);
//                break;
//            case 77:
//                player.move(4);
//                break;
//            }
//            break;
//        case 32:
//            if ((int)booms.size() < player.BoomNumMax)
//                player.SetBoom(booms, cntTime);
//            break;
//        case 27:
//            //gotoxy(0, 17);
//            system("pause");
//            break;
//        }
//    }
//}

void GameView::updataWithoutInput()
{
    //炸弹的处理
    for (int i = 0; i < (int)booms.size(); i++)
    {
        if (booms[i].BoomTime == cntTime || (booms[i].DieTime && booms[i].DieTime <= 500))
        {
            if(booms[i].DieTime == 0)
                if(mciSendString(TEXT("play boom from 0"), NULL, 0, NULL))
                    qDebug() << "error";
            for (int j = booms[i].X / 50; j <= booms[i].X / 50 + booms[i].BoomPower; j++)
            {
                if (map[j][booms[i].Y / 50] == '#')
                    break;
                //if (player.X == j && player.Y == booms[i].Y)
                if (knocked(player.X, player.Y, j * 50, booms[i].Y))
                    player.Hurt();
                for (auto it = monsters.begin(); it != monsters.end(); it++)
                    //if (it->X == j && it->Y == booms[i].Y)
                    if(knocked(it->X, it->Y, j * 50, booms[i].Y))
                        it->HP--;
                auto it = dWalls.begin();
                while (it != dWalls.end())
                {
                    if(knocked(it->X, it->Y, j * 50, booms[i].Y))
                    {
                        propertydrop(it->X, it->Y);
                        it = dWalls.erase(it);
                    }
                    else
                        it++;
                }
            }
            for (int j = booms[i].X / 50; j >= booms[i].X / 50 - booms[i].BoomPower; j--)
            {
                if (map[j][booms[i].Y / 50] == '#')
                    break;
                //if (player.X == j && player.Y == booms[i].Y)
                if(knocked(player.X, player.Y, j * 50, booms[i].Y))
                    player.Hurt();
                for (auto it = monsters.begin(); it != monsters.end(); it++)
                    //if (it->X == j && it->Y == booms[i].Y)
                    if(knocked(it->X, it->Y, j * 50, booms[i].Y))
                        it->HP--;
                auto it = dWalls.begin();
                while (it != dWalls.end())
                {
                    if(knocked(it->X, it->Y, j * 50, booms[i].Y))
                    {
                        propertydrop(it->X, it->Y);
                        it = dWalls.erase(it);
                    }
                    else
                        it++;
                }
            }
            for (int j = booms[i].Y / 50; j <= booms[i].Y / 50 + booms[i].BoomPower; j++)
            {
                if (map[booms[i].X / 50][j] == '#')
                    break;
                //if (player.Y == j && player.X == booms[i].X)
                if(knocked(player.X, player.Y, booms[i].X, j * 50))
                    player.Hurt();

                for (auto it = monsters.begin(); it != monsters.end(); it++)
                    //if (it->Y == j && it->X == booms[i].X)
                    if(knocked(it->X, it->Y, booms[i].X, j * 50))
                        it->HP--;
                auto it = dWalls.begin();
                while (it != dWalls.end())
                {
                    if(knocked(it->X, it->Y, booms[i].X, j * 50))
                    {
                        propertydrop(it->X, it->Y);
                        it = dWalls.erase(it);
                    }
                    else
                        it++;
                }
            }
            for (int j = booms[i].Y / 50; j >= booms[i].Y / 50 - booms[i].BoomPower; j--)
            {
                if (map[booms[i].X / 50][j] == '#')
                    break;
                //if (player.Y == j && player.X == booms[i].X)
                if(knocked(player.X, player.Y, booms[i].X, j * 50))
                    player.Hurt();

                for (auto it = monsters.begin(); it != monsters.end(); it++)
                    //if (it->Y == j && it->X == booms[i].X)
                    if(knocked(it->X, it->Y, booms[i].X, j * 50))
                        it->HP--;
                auto it = dWalls.begin();
                while (it != dWalls.end())
                {
                    if(knocked(it->X, it->Y, booms[i].X, j * 50))
                    {
                        propertydrop(it->X, it->Y);
                        it = dWalls.erase(it);
                    }
                    else
                        it++;
                }
            }
            booms[i].DieTime += 10;

        }
        if (booms[i].DieTime > 500)
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

    for (auto it = monsters.begin(); it != monsters.end(); it++)
    {
        if(it->movetimer == 0)
        {
            int forward = randEx() % 5;
            switch (forward)
            {
            case 1:
                if(MonsterClash(it->X / 50, it->Y / 50 - 1, it->num))
                    it->forward = forward;
                break;
            case 2:
                if(MonsterClash(it->X / 50, it->Y / 50 + 1, it->num))
                    it->forward = forward;
                break;
            case 3:
                if(MonsterClash(it->X / 50 - 1, it->Y / 50, it->num))
                    it->forward = forward;
                break;
            case 4:
                if(MonsterClash(it->X / 50 + 1, it->Y / 50, it->num))
                    it->forward = forward;
                break;
            }
            qDebug() << forward << " " << it->forward;
            it->movetimer++;
        }
        else
        {
            if(it->movetimer <= 5)
            {
                switch (it->forward)
                {
                case 1:
                    it->move(1);
                    break;
                case 2:
                    it->move(2);
                    break;
                case 3:
                    it->move(3);
                    break;
                case 4:
                    it->move(4);
                    break;
                }
                it->movetimer++;
            }
            else if(it->movetimer == 20)
            {
                it->movetimer = 0;
                it->forward = 0;
            }
            else
                it->movetimer++;
        }
    }

    //道具的处理
    for(auto it = properties.begin(); it != properties.end();)
    {
        bool e = false;
        if(knocked(player.X, player.Y, it->X, it->Y))
        {
            switch (it->effect)
            {
            case 1:
                player.BoomPower++;
                it = properties.erase(it);
                e = true;
                break;
            case 2:
                player.BoomNumMax++;
                it = properties.erase(it);
                e = true;
                break;
            }
            continue;
        }
        for (auto _it = monsters.begin(); _it != monsters.end(); _it++)
        {
            if(knocked(_it->X, _it->Y, it->X, it->Y))
            {
                it = properties.erase(it);
                e = true;
                break;
            }
        }
        if(!e)
            it++;
    }

//玩家的处理
//移动
    if(player.forward != 0) //如果有方向
    {
        if(player.movetimer < 5)
        {
            player.move(player.forward);
            player.movetimer++;
        }
        else
        {
            player.forward = 0;
            player.movetimer = 0;
        }
    }
    //无敌时间
    player.UnbeatableTimeFresh();
    for (auto it = monsters.begin(); it != monsters.end(); it++)
    {
        if (knocked(player.X, player.Y, it->X, it->Y))
            player.Hurt();
    }
}

bool GameView::knocked(int x1, int y1, int x2, int y2)
{
    int X = x1 - x2, Y = y1 - y2;
    if(X * X + Y * Y < 2500)
        return true;
    else
        return false;
}


void GameView::win()
{
//    system("cls");
//    printf(" __     ______  _    _   __          _______ _   _   _ \n");
//    printf(" \\ \\   / / __ \\| |  | |  \\ \\        / /_   _| \\ | | | |\n");
//    printf("  \\ \\_/ / |  | | |  | |   \\ \\  /\\  / /  | | |  \\| | | |\n");
//    printf("   \\   /| |  | | |  | |    \\ \\/  \\/ /   | | | . ` | | |\n");
//    printf("    | | | |__| | |__| |     \\  /\\  /   _| |_| |\\  | |_|\n");
//    printf("    |_|  \\____/ \\____/       \\/  \\/   |_____|_| \\_| (_)\n");
//    system("pause");
//    //getchar();
    timer->stop();
    mciSendString(TEXT("stop bgm"), NULL, 0, NULL);
    mciSendString(TEXT("close bgm"), NULL, 0, NULL);
    disconnect(timer, &QTimer::timeout, this, &GameView::advance);
    o = new gameover(true, Level);
    o->show();
    this->setAttribute(Qt::WA_DeleteOnClose, 1);
    this->close();
}

void GameView::failure()
{
//    system("cls");
//    printf(" __     ______  _    _    ______      _____ _      ______ _____    _ \n");
//    printf(" \\ \\   / / __ \\| |  | |  |  ____/\\   |_   _| |    |  ____|  __ \\  | |\n");
//    printf("  \\ \\_/ / |  | | |  | |  | |__ /  \\    | | | |    | |__  | |  | | | |\n");
//    printf("   \\   /| |  | | |  | |  |  __/ /\\ \\   | | | |    |  __| | |  | | | |\n");
//    printf("    | | | |__| | |__| |  | | / ____ \\ _| |_| |____| |____| |__| | |_|\n");
//    printf("    |_|  \\____/ \\____/   |_|/_/    \\_\\_____|______|______|_____/  (_)\n");
//    system("pause");
//    exit(0);
    timer->stop();
    mciSendString(TEXT("stop bgm"), NULL, 0, NULL);
    mciSendString(TEXT("close bgm"), NULL, 0, NULL);
    disconnect(timer, &QTimer::timeout, this, &GameView::advance);
    o = new gameover(false, Level);
    o->show();
    this->hide();
}

bool GameView::Clash(int X, int Y)
{
    if (map[X][Y] == '#')
        return false;
    for (int i = 0; i < (int)booms.size(); i++)
        if (X == booms[i].X && Y == booms[i].Y)
            return false;
    for(auto it = dWalls.begin(); it != dWalls.end(); it++)
        if(it->X / 50 == X && it->Y / 50 == Y)
            return false;
    for(auto it = booms.begin(); it != booms.end(); it++)
        if(it->X / 50 == X && it->Y / 50 == Y)
            return false;
    return true;
}

bool GameView::MonsterClash(int X, int Y, int num)
{
    if (GameView::Clash(X, Y))
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

void GameView::pause()
{
    timer->stop();
    mciSendString(TEXT("pause bgm"), NULL, 0, NULL);
    QMessageBox:: StandardButton result = QMessageBox::question(this, "暂停", "是否继续游戏?", QMessageBox::Yes | QMessageBox::No);
    switch (result)
    {
    case QMessageBox::Yes:
        timer->start(20);
        mciSendString(TEXT("resume bgm"), NULL, 0, NULL);
        return;
    case QMessageBox::No:
        mciSendString(TEXT("stop bgm"), NULL, 0, NULL);
        mciSendString(TEXT("close bgm"), NULL, 0, NULL);
        Widget* a = new Widget();
        a->show();
        this->setAttribute(Qt::WA_DeleteOnClose, 1);
        this->close();
        break;
    }
}

int GameView::randEx()
{
    LARGE_INTEGER seed;
    QueryPerformanceFrequency(&seed);
    QueryPerformanceCounter(&seed);
    srand(seed.QuadPart);

    return rand();
}

//void GameView::startUp()
//{
//    printf("  ______ _ _           _             _        __      ___                \n");
//    printf(" |  ____| (_)         (_)           | |       \\ \\    / (_)               \n");
//    printf(" | |__  | |_ _ __ ___  _ _ __   __ _| |_ ___   \\ \\  / / _ _ __ _   _ ___ \n");
//    printf(" |  __| | | | '_ ` _ \\| | '_ \\ / _` | __/ _ \\   \\ \\/ / | | '__| | | / __|\n");
//    printf(" | |____| | | | | | | | | | | | (_| | ||  __/    \\  /  | | |  | |_| \\__ \\\n");
//    printf(" |______|_|_|_| |_| |_|_|_| |_|\\__,_|\\__\\___|     \\/   |_|_|   \\__,_|___/\n");
//    printf("                                                                  Version 1.0\n");
//    printf("上下左右控制,空格键放炸弹,esc暂停.\n杀死所有敌人后胜利,血量降为零失败qwqq\n");

//    system("pause");
//    system("cls");
//}

void GameView::pauseclick()
{
    pause();
}

void GameView::propertydrop(int X, int Y)
{
    int n = randEx() % 100;
    if(n < 80)
        return;
    else if(n < 90)
        properties.push_back(Property(X, Y, 1));
    else
        properties.push_back(Property(X, Y, 2));
}
