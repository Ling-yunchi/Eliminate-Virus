#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>
#include <QIcon>
#include <QPalette>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QString>
#include "widget.h"
#include "gameview.h"


class gameover : public QWidget
{
    Q_OBJECT
public:
    explicit gameover(QWidget *parent = nullptr);
    explicit gameover(bool, QString);
    void paintEvent(QPaintEvent *event);

private:
    bool win;
    QString Level;
    //QPainter* painter;
    QPushButton* backToManu;
    QPushButton* again;
    QPushButton* nextLevel;

public slots:
    void backClicked();
    void againClicked();
    void nextClicked();

//signals:

};

#endif // GAMEOVER_H
