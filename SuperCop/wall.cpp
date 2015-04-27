//Alex Portolese and Sam Stein
//This file contains the coding to make the Wall work
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
}//Initializes the variables for the Wall

Wall::~Wall()
{
    delete wall;
}//Destructor

void Wall::drawWall(QPainter &painter)
{
    rectWall = new QRect(wallPosX, wallPosY, picX, picY);
    painter.drawRect(*rectWall);
    QBrush brush;
    brush.setTexture(*wall);
    painter.fillRect(*rectWall, brush);
}//Draws the wall


void Wall::setWallPosX(int x)
{
    this->wallPosX = x;
}//Mutator

void Wall::setWallPosY(int y)
{
    this->wallPosY = y;
}//Mutator


void Wall::setActive(bool active)
{
    this->active = active;
}//Mutator

int Wall::getWallPosX()
{
    return this->wallPosX;
}//Accessor

int Wall::getWallPosY()
{
    return this->wallPosY;
}//Accessor

int Wall::getWallSizeX()
{
    return this->picX;
}//Accessor

int Wall::getWallSizeY()
{
    return this->picY;
}//Accessor

bool Wall::isActive()
{
    return active;
}//Accessor

