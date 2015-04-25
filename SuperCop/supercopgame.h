//Alex Portolese and Sam Stein
//This file contains the declarations for the Functional game.
#ifndef SUPERCOPGAME_H
#define SUPERCOPGAME_H


#include "levelbase.h"
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

#include <enemy.h>
#include <donut.h>
#include <vector>
using namespace std;

namespace Ui {
class SuperCopGame;
}

class SuperCopGame : public QWidget
{
    Q_OBJECT


private:
    enum keyPressed {NONE = 0, RIGHT = 1, UP = 2, DOWN = 3, LEFT = 4};
    Ui::SuperCopGame *ui;
    int picX,picY;
    int picHeight, picWidth;

    Player *player;
    LevelBase *lb;
    QTimer *timer;
    QTimer *keyTimer;
    int lastKeyPress;

    bool isUpPressed, isDownPressed, isLeftPressed, isRightPressed;
    QWidget* parent;
    int gamescore;

    int location;
    vector<Donut*>donuts;
    vector<Enemy*>enemies;
    vector<int>donutspawn;
    vector<int>enemyspawn;
    Donut *levelend;

public:
    void paintEvent(QPaintEvent *e);
    explicit SuperCopGame(QWidget *parent = 0);
    ~SuperCopGame();

    void keyPressEvent(QKeyEvent *evt);
    void keyReleaseEvent(QKeyEvent *evt);
    void setLastKeyPress(int keyPress);
    void setPlatformX(int x);
    void obstacleMovement();
    void physics();
    void setVecs(QString level);
    void setHighScores();

    int getPlatformX();

signals:

public slots:
    void pollKey();
    void updateField();

};

#endif // SUPERCOPGAME_H
