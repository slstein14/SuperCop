#include "Player.h"
//#include "player.h"
#include "supercopgame.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>


Player::Player(QWidget *parent)
{
    posX = (parent->width() / 6) + 20;
    posY = parent->height() - 140;
    sizeX = 25;
    sizeY = 43;
    image = new QPixmap("../SuperCop/Images/Running/Run0_1.png");

    frame = 0;
    lastActionPressed = 0;
    playerDirection = 0;

    leftBound = parent->width() / 6;
    rightBound = parent->width() - (parent->width() / 6);
    ground = parent->height() - 140;

    rolling = false;
    jumping = false;
    moveRight = false;
    moveLeft = false;
    collided = true;
    playerJumpSpeed = 5; //pixels/s
    gravity = 8; //pixels/s^2
}


Player::~Player()
{
    delete image;
}


void Player::drawPlayer(QPainter &painter)
{
    painter.drawPixmap(posX, posY, sizeX, sizeY, *image);

    //For debugging purposes
    painter.setPen(Qt::red);
    painter.drawLine(rightBound, posY + 43, rightBound, posY - 43);
    painter.drawLine(leftBound, posY + 43, leftBound, posY - 43);
}


void Player::changeImage(QString str)
{
    delete image;
    image = new QPixmap(str);
}


void Player::playerScreenPos(QWidget *w = 0)
{
    //Check where player is on screen. If within a predefined rect, do not scroll screen.
    //If on edge of rect, move camera in direction player is running
    if(1 == lastActionPressed && ( this->posX + 25 < rightBound))
    {
        this->setPosX(this->getPosX() + 10);
    }

    if (4 == lastActionPressed && (this->posX > leftBound))
    {
        this->setPosX(this->getPosX() - 10);
    }
}


void Player::playerAction(int action)
{
    //If the new direction does not match the previous direction, reset the frame counter to zero.
    if(action != lastActionPressed)
    {
        frame = 0;
        lastActionPressed = action;
//        qDebug() << playerDirection;
    }

//    qDebug() << playerDirection;
    //Checks which direction is being called then runs the appropriate function
    switch (action)
    {
    case RIGHT:
        run();
        break;
    case UP:
        jump();
        break;
    case DOWN:
        roll();
        break;
    case LEFT:
        runInverted();
        break;
    case NONE:
        standBy();
        break;
    }

    playerScreenPos();
}


void Player::jump()
{
//    frame++;

//    if(0 < this->getFrame() && 15 > this->getFrame())
//    {
        QString imagePath;
        jumping = true;
        collided = false;
//        if(0 < this->getFrame() && 5 > this->getFrame())
//        {
            switch(playerDirection)
            {
            case WEST:
                imagePath = QString("../SuperCop/Images/Running/Run1_1.png");
                changeImage(imagePath);
                fallTime = playerJumpSpeed / gravity;
                posY = static_cast<int>((playerJumpSpeed * fallTime) - (0.5 * gravity * (fallTime * fallTime)));
                break;
            case EAST:
                imagePath = QString("../SuperCop/Images/Running/Run0_1.png");
                changeImage(imagePath);
                fallTime = playerJumpSpeed / gravity;
                posY = static_cast<int>((playerJumpSpeed * fallTime) - (0.5 * gravity * (fallTime * fallTime)));
                break;
            case STAND:
                break;
            }
//        }
//        else
//        {
//            SuperCopGame *w;
//            switch(playerDirection)
//            {
//            case WEST:
//                imagePath = QString("../SuperCop/Images/Running/Run1_1.png");
//                changeImage(imagePath);
//                w->physics();
//                break;
//            case EAST:
//                imagePath = QString("../SuperCop/Images/Running/Run0_1.png");
//                changeImage(imagePath);
//                w->physics();
//                break;
//            case STAND:
//                break;
//            }
//        }
//    }
//    else
//    {
//        jumping = false;
//        standBy();
//        this->setPosY(ground);

//    }
}//Player State


void Player::roll()
{
    frame++;

    if(0 < this->getFrame() && 9 > this->getFrame())
    {    
        QString imagePath;
        rolling = true;
        if(0 < this->getFrame() && 4 > this->getFrame())
        {
            switch(playerDirection)
            {
            case WEST:
                this->setPosX(this->getPosX() - 8);
                imagePath = QString("../SuperCop/Images/Rolling/Roll1_%1.png").arg(QString::number(frame));
                changeImage(imagePath);
                break;
            case EAST:
                this->setPosX(this->getPosX() + 8);
                imagePath = QString("../SuperCop/Images/Rolling/Roll0_%1.png").arg(QString::number(frame));
                changeImage(imagePath);
                break;
            case STAND:
                break;
            }
        }
        else
        {
            switch(playerDirection)
            {
            case WEST:
                this->setPosX(this->getPosX() - 3);
                imagePath = QString("../SuperCop/Images/Rolling/Roll1_%1.png").arg(QString::number(frame));
                changeImage(imagePath);
                break;
            case EAST:
                this->setPosX(this->getPosX() + 3);
                imagePath = QString("../SuperCop/Images/Rolling/Roll0_%1.png").arg(QString::number(frame));
                changeImage(imagePath);
                break;
            case STAND:
                break;
            }
        }
    }
    else
    {
        rolling == false;
        standBy();
    }

}//Player State


void Player::run()
{
    frame++;
    QString imagePath = QString("../SuperCop/Images/Running/Run0_%1.png").arg(frame);

    if(0 < this->getFrame() && 4 > this->getFrame())
    {
        changeImage(imagePath);
        moveRight = true;
        playerDirection = 1;
    }
    else
    {
        frame = 0;
        moveRight = false;
        playerDirection = 1;
        changeImage("../SuperCop/Images/Running/Run0_1.png");
    }
}//Player State


void Player::runInverted()
{
    frame++;

    QString imagePath = QString("../SuperCop/Images/Running/Run1_%1.png").arg(frame);

    if(0 < this->getFrame() && 4 > this->getFrame())
    {
        moveLeft = true;
        changeImage(imagePath);
        playerDirection = -1;
    }
    else
    {
        frame = 0;
        moveLeft = false;
        changeImage("../SuperCop/Images/Running/Run1_1.png");
        playerDirection = -1;
    }
}//Player State

void Player::standBy()
{
    //Checks which direction the player was moving last then sets the appropiate standing image
    if(1 == playerDirection)
    {
        changeImage("../SuperCop/Images/Running/Run0_1.png");
        collided = true;
    }
    if(-1 == playerDirection)
    {
        changeImage("../SuperCop/Images/Running/Run1_1.png");
        collided = true;
    }
}


int Player::getFrame()
{
    return frame;
}//Accessor

int Player::getLeftBound()
{
    return leftBound;
}//Accessor

int Player::getRightBound()
{
    return rightBound;
}

int Player::getPlayerDirection()
{
    return playerDirection;
}

int Player::getGround()
{
    return ground;
}

int Player::getSpeedY()
{
    return playerJumpSpeed;
}//Accessor


bool Player::isRolling()
{
    return rolling;
}//Accessor


bool Player::isJumping()
{
    return jumping;
}//Accessor



bool Player::isMoveRight()
{
    return moveRight;
}//Accessor



bool Player::isMoveLeft()
{
    return moveLeft;
}

bool Player::isCollided()
{
    return collided;
}//Accessor


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
}

void Player::setCollided(bool collided)
{
    this->collided = collided;
}

void Player::setSpeedY(int y)
{
    this->playerJumpSpeed = y;
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
