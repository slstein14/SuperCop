#ifndef WALL_H
#define WALL_H

#include "donut.h"
#include "enemy.h"
#include <QPixmap>
#include <QPainter>
#include <QWidget>


class Wall
{
private:
    QPixmap *wall;
    QPixmap *fire;
    QRect *rectWall;
//    QWidget *par;
    int picX, picY, firePicX, firePicY;
    int gameWindow, wallState;
    int wallPosX, wallPosY, firePosX, firePosY;

    bool wallHasFire, wallHasEnemy, active;

    enum wallType {PLAIN = 0, FIRE = 1, ENEMY = 2};

public:
    Wall(QWidget *parent);
    ~Wall(); 

    void drawWall(QPainter &painter);
    void drawFire(QPainter &painter);

    void setWallPosX(int x);
    void setWallPosY(int y);
    void setFirePosX(int x);
    void setFirePosY(int y);
    void setWallOnFire(bool fire);
    void setEnemyOnWall(bool enemy);
    void setWallState(enum Wall::wallType state);
    void setActive(bool active);

    int getWallPosX();
    int getWallPosY();
    int getWallSizeX();
    int getWallSizeY();

    int getFirePosX();
    int getFirePosY();

    int getWallType();

    bool isActive();
};

#endif // WALL_H
