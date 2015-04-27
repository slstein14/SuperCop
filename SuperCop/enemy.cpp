//Alex Portolese and Sam Stein
//This file contains the coding to make the enemies functional.
#include "enemy.h"
#include <QDebug>

Enemy::Enemy(QWidget *parent)
{

    posX = parent->width() ;
    posY = parent->height() - 140;
    sizeX = 40;
    sizeY = 40;
    robot = new QPixmap("../SuperCop/Images/Enemy/enemy0.png");
    active=false;
    direction=0;
}//initializes the enemy variables

Enemy::~Enemy()
{
    delete robot;

}//Destructor

void Enemy::drawEnemy(QPainter &painter)
{
    painter.drawPixmap(posX, posY, sizeX, sizeY, *robot);
}//Draws the enemy image

void Enemy::changeImage(QString str)
{
    delete robot;
    robot = new QPixmap(str);
}//allow for the enemy image to be changed


void Enemy::setPosX(int x)
{
    posX=x;
}//Mutator

void Enemy::setPosY(int y)
{
    posY=y;
}//Mutator

void Enemy::setSizeX(int x)
{
    sizeX=x;
}//Mutator

void Enemy::setSizeY(int y)
{
    sizeY=y;
}//Mutator

int Enemy::getPosX()
{
    return posX;
}//Accessor

int Enemy::getPosY()
{
    return posY;
}//Accessor

int Enemy::getSizeX()
{
    return sizeX;
}//Accessor

int Enemy::getSizeY()
{
    return sizeY;
}//Accessor

bool Enemy::getActive()
{
    return active;
}//Mutator

void Enemy::setActive(bool act)
{
    active=act;
}//Accessor

void Enemy::setDirection(int direc)
{
    direction=direc;
    switch(direction)
    {
    case RIGHT:
        changeImage("../SuperCop/Images/Enemy/enemy0.png");
        break;
    case LEFT:
        changeImage("../SuperCop/Images/Enemy/enemy1.png");
        break;
    }
}//Mutator

int Enemy::getDirection()
{
    return direction;
}//Accessor
