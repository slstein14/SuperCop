//Alex Portolese and Sam Stein
//This file contains the coding to make the enemies functional.
#include "enemy.h"
#include "supercopgame.h"
#include <QDebug>

Enemy::Enemy(QWidget *parent)
{

    posX = 620;
    posY = parent->height() - 140;
    sizeX = 45;
    sizeY = 45;
    robot = new QPixmap("../SuperCop/Images/Robot/robot.png");
    active=false;
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
