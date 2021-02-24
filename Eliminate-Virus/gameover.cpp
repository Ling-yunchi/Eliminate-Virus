#include "gameover.h"

gameover::gameover(QWidget *parent) : QWidget(parent)
{

}

gameover::gameover(bool win, QString level)
{
    this->win = win;

    setFixedSize(850, 850);
    setWindowTitle("Eliminate-Virus");
    setWindowIcon(QIcon("../src/icon.ico"));
    setAutoFillBackground(true);

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QBrush(QPixmap("../src/bg.jpg").scaled(width(), height()))));
    this->setPalette(palette);

    Level = level;

    if(win)
    {
        mciSendString(TEXT("open ../src/win.wav alias over"), NULL, 0, NULL);
        mciSendString(TEXT("play over from 0"), NULL, 0, NULL);
        if(Level != "1-6")
        {
            nextLevel = new QPushButton("下一关", this);
            nextLevel->move(375, 450);
            connect(nextLevel, &QPushButton::clicked, this, &gameover::nextClicked);
        }
        backToManu = new QPushButton("返回菜单", this);
        backToManu->move(375, 500);
        connect(backToManu, &QPushButton::clicked, this, &gameover::backClicked);
    }
    else
    {
        mciSendString(TEXT("open ../src/lose.wav alias over"), NULL, 0, NULL);
        mciSendString(TEXT("play over from 0"), NULL, 0, NULL);
        again = new QPushButton("重试", this);
        again->move(375, 450);
        connect(again, &QPushButton::clicked, this, &gameover::againClicked);

        backToManu = new QPushButton("返回菜单", this);
        backToManu->move(375, 500);
        connect(backToManu, &QPushButton::clicked, this, &gameover::backClicked);
    }
}

void gameover::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);

    QFont font("Microsoft YaHei", 15, 75);
    painter.setFont(font);

    if(win)
    {
        painter.drawText(375, 250, "胜利!");
        if(Level == "1-5")
            painter.drawText(350, 300, "前面可是地狱哦~");
        if(Level == "1-6")
        {
            painter.drawText(300, 300, "虽然不知道你是真的把病毒全鲨了");
            painter.drawText(300, 350, "还是按下了?来到这里");
            painter.drawText(300, 400, "恭喜你通关了!!!");
            painter.drawText(500, 800, "后续可能不定期更新(小声BB");
        }
    }
    else
    {
        painter.drawText(375, 300, "失败!");
    }
}

void gameover::backClicked()
{
    mciSendString(TEXT("stop over"), NULL, 0, NULL);
    mciSendString(TEXT("close over"), NULL, 0, NULL);
    Widget* a = new Widget();
    a->show();
    this->setAttribute(Qt::WA_DeleteOnClose, 1);
    this->close();
}
void gameover::againClicked()
{
    mciSendString(TEXT("stop over"), NULL, 0, NULL);
    mciSendString(TEXT("close over"), NULL, 0, NULL);
    GameView* g = new GameView(Level);
    g->show();
    this->setAttribute(Qt::WA_DeleteOnClose, 1);
    this->close();

}
void gameover::nextClicked()
{
    if(Level == "1-1")
        Level = "1-2";
    else if(Level == "1-2")
        Level = "1-3";
    else if(Level == "1-3")
        Level = "1-4";
    else if(Level == "1-4")
        Level = "1-5";
    else if(Level == "1-5")
        Level = "1-6";

    mciSendString(TEXT("stop over"), NULL, 0, NULL);
    mciSendString(TEXT("close over"), NULL, 0, NULL);
    GameView* g = new GameView(Level);
    g->show();
    this->setAttribute(Qt::WA_DeleteOnClose, 1);
    this->close();
}
