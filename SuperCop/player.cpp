#include "Player.h"
#include "player.h"
#include "supercopgame.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>

Player::Player(QWidget *parent)
{
    posX = 10;
    posY = parent->height() - 220;
    sizeX = 50;
    sizeY = 86;
    image = new QPixmap("../SuperCop/Images/player.png");
    animationTimer = new QTimer();
    animationTimer->setInterval(17);
    frame = 0;
    animationTimer->start();
    lastActionPressed = 0;

//    playerScreenPos(parent);
}

Player::~Player()
{
    delete image;
    animationTimer->stop();
    delete animationTimer;
}

void Player::drawPlayer(QPainter &painter)
{
    painter.drawPixmap(posX, posY, sizeX, sizeY, *image);
}

void Player::changeImage(QString str)
{
    delete image;
    image = new QPixmap(str);
}

void Player::playerScreenPos(QWidget *w)
{

}

int Player::playerAction(int action)
{
    //If the new direction does not match the previous direction, reset the frame counter to zero.
    if(action != lastActionPressed)
    {
        qDebug() << "Last action: " << lastActionPressed;
        qDebug() << "New aciton: " << action;
        frame = 0;
        lastActionPressed = action;
    }

    //Checks which direction is being called then runs the appropriate function
    switch (action)
    {
    case RIGHT:
        /*return*/ run();
        return 0;
        break;
    case UP:
        return jump();
        break;
    case DOWN:
        return roll();
        break;
    case LEFT:
        /*return */runInverted();
        return 0;
        break;
    case NONE:
        standBy();
        break;
    }

    lastActionPressed = action;
}

int Player::jump()
{
    return 0;
    //IGNORE THIS FUNCTION FOR NOW
}

int Player::roll()
{
        frame++;
        QString imagePath = QString("../SuperCop/Images/Rolling/Roll%1.png").arg(QString::number(frame));

        //Resizes the player to half size
        sizeX = 25;
        sizeY = 40;

        if(9 > frame)
        {
            changeImage(imagePath);
//            return 3;
        }
        else
        {
            //After one loop, return the player to normal size and continue running to the right.
            sizeX = 50;
            sizeY = 81;
            frame = 0;

            return 0;
        }
}

int Player::run()
{
    frame++;
    QString imagePath = QString("../SuperCop/Images/Running/Run0_%1.png").arg(frame);

    if(4 > frame)
    {
        changeImage(imagePath);
//        return 1;
    }
    else
    {
        frame = 0;
        return 0;
    }
}

int Player::runInverted()
{
    frame++;
    QString imagePath = QString("../SuperCop/Images/Running/Run1_%1.png").arg(frame);

    if(4 > frame)
    {
        changeImage(imagePath);
//        return 0;
    }
    else
    {
        frame = 0;
        return 0;
    }
}

void Player::standBy()
{
    if(lastActionPressed == 1)
        changeImage("../SuperCop/Images/Running/Run0_1.png");

    if(lastActionPressed == 4)
        changeImage("../SuperCop/Images/Running/Run1_1.png");
}

void Player::setPosX(int x)
{
    posX=x;
}//Mutator

void Player::setPosY(int y)
{
    posY=y;
}//Mutator

void Player::setSizeX(int x)
{
    sizeX=x;
}//Mutator

void Player::setSizeY(int y)
{
    sizeY=y;
}//Mutator

int Player::getPosX()
{
    return posX;
}//Accessor

int Player::getPosY()
{
   return posY;
}//Accessor

int Player::getSizeX()
{
  return sizeX;
}//Accessor

int Player::getSizeY()
{
    return sizeY;
}//Accessor
