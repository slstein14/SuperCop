//Alex Portolese and Sam Stein
//This file contains the coding to make the floor work
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

    generateLevel = new QTimer();
    generateLevel->setInterval(50);
}//Initializes the variables for the floor

LevelBase::~LevelBase()
{
 delete floor;
}//Destructor

void LevelBase::drawLevel(QPainter &painter)
{
    drawLevelBase(painter);
}//Calls the various draw functions

void LevelBase::drawLevelBase(QPainter &painter)
{
    rect = new QRect(0, floorStart, gameWindow, 32);
    painter.drawRect(*rect);
    QBrush brush;
    brush.setTexture(*floor);
    painter.fillRect(*rect, brush);
}//Draws the floor

void LevelBase::drawLevel()
{
    //Random Level Generation
}
