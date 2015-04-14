#ifndef SUPERCOPGAME_H
#define SUPERCOPGAME_H


#include "player.h"

#include <QWidget>
#include <QGraphicsItem>
#include <QtCore>
#include <QtGui>
#include <QQmlEngine>
#include <QQuickView>
#include <QTimer>
#include <QKeyEvent>
#include <QPixmap>
#include <QMessageBox>

namespace Ui {
class SuperCopGame;
}

class SuperCopGame : public QWidget
{
    Q_OBJECT


private:
    enum keyPressed {NONE = 0, RIGHT = 1, UP = 2, DOWN = 3, LEFT = 4};
    Ui::SuperCopGame *ui;
    QPixmap* robot;
    int picX,picY;
    int picHeight, picWidth;
    Player *player;
    QTimer *timer;
    int lastKeyPress;
    QWidget* parent;
    int gamescore;

public:
    void paintEvent(QPaintEvent *e);
    explicit SuperCopGame(QWidget *parent = 0);
    ~SuperCopGame();

    void keyPressEvent(QKeyEvent *evt);
    void setLastKeyPress(int keyPress);

signals:

public slots:
    void updateField();
};

#endif // SUPERCOPGAME_H
