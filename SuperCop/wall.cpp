#include "wall.h"

Wall::Wall(QWidget *parent)
{
    wall = new QPixmap("../SuperCop/Images/Wall/0.png");
    fire = new QPixmap("../SuperCop/Images/Fire/fire.png");

    gameWindow = parent->width();
    wallPosY = parent->height() - 140;
    wallPosX = gameWindow + 20;

    picX = 32;
    picY = 50;

    firePicX = 30;
    firePicY = 21;
    firePosX = wallPosX + 1;
    firePosY = wallPosY - 21;

    wallState = 0;
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

    if(wallState == FIRE)
    {
        drawFire(painter);
    }
}

void Wall::drawFire(QPainter &painter)
{
    painter.drawPixmap(firePosX, firePosY, firePicX, firePicY, *fire);
}

void Wall::setWallPosX(int x)
{
    this->wallPosX = x;
}

void Wall::setWallPosY(int y)
{
    this->wallPosY = y;
}

void Wall::setFirePosX(int x)
{
    this->firePosX = x;
}

void Wall::setWallOnFire(bool fire)
{
    this->wallHasFire = fire;
}

void Wall::setEnemyOnWall(bool enemy)
{
    this->wallHasEnemy = enemy;
}

void Wall::setWallState(enum Wall::wallType state)
{
    this->wallState = state;
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

int Wall::getFirePosX()
{
    return firePosX;
}

int Wall::getFirePosY()
{
    return firePosY;
}

int Wall::getWallType()
{
    switch(wallState)
    {
    case PLAIN:
        return 0;
        break;
    case FIRE:
        return 1;
        break;
    case ENEMY:
        return 2;
        break;
    }
}

bool Wall::isActive()
{
    return active;
}

