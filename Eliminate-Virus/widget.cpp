#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setFixedSize(850, 850);//设置固定窗口大小
    setWindowTitle("Eliminate-Virus");//设置窗口标题
    setWindowIcon(QIcon("../src/icon.ico"));//设置窗口图标




    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap("../src/bg.jpg").scaled(width(), height())));
    this->setPalette(palette);

    this->Title = new QLabel(this);
    Title->move(70, 100);
    Title->setPixmap(QPixmap("../src/lable.png"));

    this->Start = new QPushButton("开始", this);
    Start->move(375, 400);
    connect(Start, &QPushButton::clicked, this, &Widget::startclick);

    this->Help = new QPushButton("帮助", this);
    Help->move(375, 450);
    connect(Help, &QPushButton::clicked, this, &Widget::helpclick);

    this->Exit = new QPushButton("退出", this);
    Exit->move(375, 500);
    connect(Exit, &QPushButton::clicked, this, &Widget::close);

    if(mciSendString(TEXT("open ../src/menu.wav alias menu"), NULL, 0, NULL))
    {
        qDebug() << "打开失败";
    }

    if(mciSendString(TEXT("play menu"), NULL, 0, NULL))
    {
        qDebug() << "播放背景音乐失败！";
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::startclick()
{
    w = new chooselevelwidget(this);
    w->setLastW(this);
    w->show();
}

void Widget::helpclick()
{
    QMessageBox::about(this, "HELP", "上下左右键控制人物移动,空格键放置炸弹。\n"
                       "在移动中不可放置炸弹(极大增加游戏难度\n"
                       "esc键可以暂停_(:з」∠)_\n"
                       "游戏中按下？有小惊喜qwqq");
}
