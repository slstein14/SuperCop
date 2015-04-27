#ifndef WALL_H
#define WALL_H

#include <QPixmap>
#include <QPainter>
#include <QWidget>

class Wall
{
private:
    QPixmap *wall;
    QRect *rectWall;
    int picX, picY;
    int gameWindow;
    int wallPosX, wallPosY;
    bool  active;

public:
    Wall(QWidget *parent);
    ~Wall();

    void drawWall(QPainter &painter);
    void setWallPosX(int x);
    void setWallPosY(int y);
    void setActive(bool active);
    int getWallPosX();
    int getWallPosY();
    int getWallSizeX();
    int getWallSizeY();
    int getWallType();
    bool isActive();
};

#endif // WALL_H
