#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIcon>
#include <QPalette>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib,"Winmm.lib")


#include "chooselevelwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

//protected:
//    void paintEvent(QPaintEvent *);

private:
    Ui::Widget *ui;

    QLabel *Title;
    QPushButton *Start;
    QPushButton *Help;
    QPushButton *Exit;
    chooselevelwidget *w;
public slots:
    void startclick();
    void helpclick();


};
#endif // WIDGET_H
