#include "wall.h"

Wall::Wall(QWidget *parent)
{
    wall = new QPixmap("../SuperCop/Images/Wall/0.png");

    gameWindow = parent->width();
    wallPosY = parent->height() - 140;
    wallPosX = gameWindow + 50;

    picX = 32;
    picY = 50;
    active = false;
}

Wall::~Wall()
{
    delete wall;
}

void Wall::drawWall(QPainter &painter)
{
    rectWall = new QRect(wallPosX, wallPosY, picX, picY);
    painter.drawRect(*rectWall);
    QBrush brush;
    brush.setTexture(*wall);
    painter.fillRect(*rectWall, brush);

}


void Wall::setWallPosX(int x)
{
    this->wallPosX = x;
}

void Wall::setWallPosY(int y)
{
    this->wallPosY = y;
}


void Wall::setActive(bool active)
{
    this->active = active;
}

int Wall::getWallPosX()
{
    return this->wallPosX;
}

int Wall::getWallPosY()
{
    return this->wallPosY;
}

int Wall::getWallSizeX()
{
    return this->picX;
}

int Wall::getWallSizeY()
{
    return this->picY;
}

bool Wall::isActive()
{
    return active;
}

