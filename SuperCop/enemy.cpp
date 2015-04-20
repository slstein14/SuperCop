#include "enemy.h"
#include "supercopgame.h"
#include <QDebug>
#include <QTimer>

Enemy::Enemy(QWidget *parent)
{

    posX = 620;
    posY = parent->height() - 220;
    sizeX = 85;
    sizeY = 85;
    robot = new QPixmap("../SuperCop/Images/Robot/robot.png");
    moveTimer = new QTimer();
    moveTimer->setInterval(10);
//    frame = 0;
    moveTimer->start();
    speed=5;
}

Enemy::~Enemy()
{
    delete robot;
    moveTimer->stop();
    delete moveTimer;
}//Destructor

void Enemy::drawEnemy(QPainter &painter)
{
    painter.drawPixmap(posX, posY, sizeX, sizeY, *robot);
    posX-=speed;
}

void Enemy::changeImage(QString str)
{
    delete robot;
    robot = new QPixmap(str);
}


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

void Enemy::setSpeed(int speed)
{
    this->speed=speed;
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

int Enemy::getSpeed()
{
   return speed;
}//Accessor

