#include "chooselevelwidget.h"

chooselevelwidget::chooselevelwidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(850, 850);
    setWindowTitle("Eliminate-Virus");
    setWindowIcon(QIcon("../src/icon.ico"));
    setAutoFillBackground(true);


    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QBrush(QPixmap("../src/bg.jpg").scaled(width(), height()))));
    this->setPalette(palette);

    Level = new QComboBox(this);
    Level->move(375, 200);
    Level->addItem("请选择关卡");
    level = "请选择关卡"; //初始化关卡选择qwqq
    for(int i = 1; i <= 6; i++)
    {
        Level->addItem(QString::asprintf("1-%d", i));
    }
    Level->addItem("敬请期待!");

    connect(Level, &QComboBox::currentTextChanged, this, &chooselevelwidget::levelchanged);

    StartGame = new QPushButton("开始游戏", this);
    StartGame->move(375, 450);
    connect(StartGame, &QPushButton::clicked, this, &chooselevelwidget::startGameclicked);

    Back = new QPushButton("返回", this);
    Back->move(375, 500);
    connect(Back, &QPushButton::clicked, this, &chooselevelwidget::backclicked);

}

void chooselevelwidget::backclicked()
{
    this->close();
}

void chooselevelwidget::setLastW(QWidget *lastW)
{
    this->lastW = lastW;
}

void chooselevelwidget::levelchanged()
{
    level = Level->currentText();
    qDebug() << level;
}

void chooselevelwidget::startGameclicked()
{
    if(level == "请选择关卡")
    {
        QMessageBox::warning(this, "warning", "未选择关卡!!!");
    }
    else if(level == "敬请期待!")
    {
        QMessageBox::warning(this, "qwqq", "敬请期待!!!");
    }
    else
    {
        mciSendString(TEXT("stop menu"), NULL, 0, NULL);
        mciSendString(TEXT("close menu"), NULL, 0, NULL);
        this->parentWidget()->hide();
        g = new GameView(level);
        g->show();
    }
}
