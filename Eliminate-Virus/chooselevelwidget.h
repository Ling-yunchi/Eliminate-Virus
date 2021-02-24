#ifndef CHOOSELEVELWIDGET_H
#define CHOOSELEVELWIDGET_H

#include <QWidget>
#include <QIcon>
#include <QPalette>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QMessageBox>
#include "gameview.h"

class chooselevelwidget : public QWidget
{
    Q_OBJECT
public:
    explicit chooselevelwidget(QWidget *parent = nullptr);

    void setLastW(QWidget*);

private:
    QWidget *lastW;
    QComboBox *Level;
    QPushButton *StartGame;
    QPushButton *Back;
    QString level;
    GameView *g;


signals:

public slots:
    void startGameclicked();
    void backclicked();
    void levelchanged();

};

#endif // CHOOSELEVELWIDGET_H

