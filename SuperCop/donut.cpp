#include "donut.h"
#include "supercopgame.h"
#include <QDebug>

Donut::Donut(QWidget *parent)
{
    windowwidth=parent->width();
    posX = (620);
    posY = parent->height() - 140;
    sizeX = 20;
    sizeY = 20;
    donut = new QPixmap("../SuperCop/Images/Donut/Donut.png");
    active=false;
}

Donut::~Donut()
{
    delete donut;
}//clears potential memory leaks

void Donut::drawDonut(QPainter &painter)
{
    painter.drawPixmap(posX, posY, sizeX, sizeY, *donut);
}

void Donut::changeImage(QString str)
{
    delete donut;
    donut = new QPixmap(str);
}

void Donut::setPosX(int x)
{
    posX=x;
}//Mutator

void Donut::setPosY(int y)
{
    posY=y;
}//Mutator

void Donut::setSizeX(int x)
{
    sizeX=x;
}//Mutator

void Donut::setSizeY(int y)
{
    sizeY=y;
}//Mutator


int Donut::getPosX()
{
    return posX;
}//Accessor

int Donut::getPosY()
{
    return posY;
}//Accessor

int Donut::getSizeX()
{
    return sizeX;
}//Accessor

int Donut::getSizeY()
{
    return sizeY;
}//Accessor

bool Donut::getActive()
{
    return active;
}//Mutator

void Donut::setActive(bool act)
{
    active=act;
}//Accessor
