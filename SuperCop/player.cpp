//Alex Portolese and Sam Stein
//This file contains the coding to make the player functional.
#include "Player.h"
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
    playerDirection = 1;

    leftBound = parent->width() / 5;
    rightBound = parent->width() - (parent->width() / 3);
    ground = parent->height() - 140;

    rolling = false;
    jumping = false;
    moveRight = false;
    moveLeft = false;
    ascend = false;
    playerOnWall = false;
    playerOnPlatform = false;
    onGround = true;
}//initializes the player variables

Player::~Player()
{
    delete image;
}//Destructor


void Player::drawPlayer(QPainter &painter)
{
    painter.drawPixmap(posX, posY, sizeX, sizeY, *image);

    //For debugging purposes
    painter.setPen(Qt::red);
    painter.drawLine(rightBound, posY + 43, rightBound, posY - 43);
    painter.drawLine(leftBound, posY + 43, leftBound, posY - 43);
}//Draws the player


void Player::changeImage(QString str)
{
    delete image;
    image = new QPixmap(str);
}//Allows the player icon to be changed


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
}//Controls whether the screen moves or the player does


void Player::playerAction(int action)
{
    //If the new direction does not match the previous direction, reset the frame counter to zero.
    if(action != lastActionPressed)
    {
        frame = 0;
        lastActionPressed = action;
    }
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
}//Calls the various player controlled movement functions


void Player::jump()
{
    frame++;

      if(0 < this->getFrame() && 15 > this->getFrame())
        {
            QString imagePath;
            if(0 < this->getFrame() && 8 > this->getFrame())
            {
                ascend = true;
                switch(playerDirection)
                {
                case WEST:
                    imagePath = QString("../SuperCop/Images/Running/Run1_1.png");
                    changeImage(imagePath);
                    posY -= 30;
                    break;
                case EAST:
                    imagePath = QString("../SuperCop/Images/Running/Run0_1.png");
                    changeImage(imagePath);
                    posY -= 30;
                    break;
                case STAND:
                    break;
                }
            }
            else
            {
                ascend = false;
                switch(playerDirection)
                {
                case WEST:
                    imagePath = QString("../SuperCop/Images/Running/Run1_1.png");
                    changeImage(imagePath);
//                    posY += 10;
                    break;
                case EAST:
                    imagePath = QString("../SuperCop/Images/Running/Run0_1.png");
                    changeImage(imagePath);
//                    posY += 10;
                    break;
                case STAND:
                    break;
                }
            }
        }
        else
        {
            standBy();
        }
}//Controls Player Jumps


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
                if(this->getPosX() - 8 > leftBound)
                    this->setPosX(this->getPosX() - 8);

                imagePath = QString("../SuperCop/Images/Rolling/Roll1_%1.png").arg(QString::number(frame));
                changeImage(imagePath);
                break;
            case EAST:
                if(this->getPosX() + 8 < rightBound)
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
                if(this->getPosX() - 3 > leftBound)
                    this->setPosX(this->getPosX() - 3);

                imagePath = QString("../SuperCop/Images/Rolling/Roll1_%1.png").arg(QString::number(frame));
                changeImage(imagePath);
                break;
            case EAST:
                if(this->getPosX() + 3 < rightBound)
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
        rolling = false;
        standBy();
    }

}//Controls Player Rolls

void Player::run()
{
    if(this->isJumping() && !this->isAscending() && !this->isOnGround() && !this->isOnPlatform() && !this->isOnWall())
    {
        if(playerDirection == 1)
        {
            posY += 15;
            posX += 1;
        }
        else if(playerDirection == -1)
        {
            posY += 10;
            posX -= 1;
        }
        else
        {
            posY += 15;
            posX = posX;
        }

    }
    else
    {
        jumping = false;
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
    }
}//Controls Player Running right

void Player::runInverted()
{
    if(this->isJumping() && !this->isAscending() && !this->onGround)
    {

    }
    else
    {
        frame++;
        jumping = false;
        QString imagePath = QString("../SuperCop/Images/Running/Run1_%1.png").arg(frame);

        if(0 < this->getFrame() && 4 > this->getFrame())
        {
            changeImage(imagePath);
            moveLeft = true;
            playerDirection = -1;
        }
        else
        {
            frame = 0;
            moveLeft = false;
            playerDirection = -1;
            changeImage("../SuperCop/Images/Running/Run1_1.png");
        }
    }
}//Controls Player Running Left

void Player::standBy()
{
    //Checks which direction the player was moving last then sets the appropiate standing image
    if(1 == playerDirection)
    {
        changeImage("../SuperCop/Images/Running/Run0_1.png");
    }
    if(-1 == playerDirection)
    {
        changeImage("../SuperCop/Images/Running/Run1_1.png");
    }
}//Controls Player Stopped

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
}//Accessor


int Player::getPlayerDirection()
{
    return playerDirection;
}//Accessor


int Player::getGround()
{
    return ground;
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
}//Accessor
<<<<<<< HEAD

bool Player::isOnGround()
{
    return onGround;
}

bool Player::isAscending()
{
    return ascend;
}

bool Player::isOnPlatform()
{
    return playerOnPlatform;
}

bool Player::isOnWall()
{
    return playerOnWall;
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
}//Mutator

void Player::setOnGround(bool onGround)
{
    this->onGround = onGround;
}//Mutator


void Player::setJumping(bool jump)
{
    this->jumping = jump;
}//Mutator

void Player::setOnWall(bool onWall)
{
    this->playerOnWall = onWall;
}//Mutator


void Player::setOnPlatform(bool onPlat)
{
    this->playerOnPlatform = onPlat;
}//Accessor

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
