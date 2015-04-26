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

}

LevelBase::~LevelBase()
{
    delete floor;
}

void LevelBase::drawLevel(QPainter &painter)
{
    drawLevelBase(painter);
}

void LevelBase::drawLevelBase(QPainter &painter)
{
    rect = new QRect(0, floorStart, gameWindow, 32);
    painter.drawRect(*rect);
    QBrush brush;
    brush.setTexture(*floor);
    painter.fillRect(*rect, brush);
}

void LevelBase::drawLevel()
{
    //Random Level Generation
}
