#include "levelbase.h"
#include <QDebug>

LevelBase::LevelBase(QWidget *parent)
{
    floor = new QPixmap("../SuperCop/Images/Wall/0.png");
    floorStart = parent->height() - 100;
    picX = 16;
    picY = 16;
    floorLength = parent->width() / 28.0;
    gameWindow = parent->width();
    platformHeight = parent->height() - 160;
    platformPosX = gameWindow - (gameWindow / 6);
    stairPosX = gameWindow / 2;
    stairPosY = floorStart - 16;

    step1Y = floorStart - 16;
    step2Y = step1Y - 16;
    step3Y = step2Y - 16;
    step4Y = step3Y - 16;
}

LevelBase::~LevelBase()
{

}

void LevelBase::drawLevel(QPainter &painter)
{
    drawLevelBase(painter);
    drawPlatform(painter);
    drawStairs(painter);
}

void LevelBase::drawLevelBase(QPainter &painter)
{
    rect = new QRect(0, floorStart, gameWindow, 32);
    painter.drawRect(*rect);
    QBrush brush;
    brush.setTexture(*floor);
    painter.fillRect(*rect, brush);
}

void LevelBase::drawPlatform(QPainter &painter)
{
    rectPlat = new QRect(platformPosX, platformHeight, 48, 16);
    painter.drawRect(*rectPlat);
    QBrush brush;
    brush.setTexture(*floor);
    painter.fillRect(*rectPlat, brush);
}

void LevelBase::drawStairs(QPainter &painter)
{
    //Declare and intialize stair array
    int stairs[4][4] =
    {
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {1, 1, 1, 0},
        {1, 1, 1, 1}
    };

    //Draw Array
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(stairs[i][j] != 0)
            {
                painter.drawPixmap(stairPosX + i * picX, stairPosY - j * picY, picX, picY, *floor);
            }
        }
    }
}

void LevelBase::setPlatformPosX(int x)
{
    this->platformPosX = x;
}

void LevelBase::setStairPosX(int x)
{
    this->stairPosX = x;
}

int LevelBase::getStairPosX()
{
    return stairPosX;
}

int LevelBase::getPlatformPosX()
{
    return platformPosX;
}

int LevelBase::getPlatformPosY()
{
    return platformHeight;
}

int LevelBase::getPlatformEnd()
{
    return platformPosX + 48;
}



