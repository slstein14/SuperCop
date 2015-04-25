//Alex Portolese and Sam Stein
//This file contains the declarations for the Level floor.
#ifndef LEVELBASE_H
#define LEVELBASE_H

#include <QPainter>
#include <QWidget>
#include <QRect>


class LevelBase
{
private:
    QPixmap *floor;
    int floorStart;
    double floorLength;
    int floorHeight;
    int picX;
    int picY;
    int gameWindow;
    int platformHeight;
    int platformPosX;
    int stairPosX, stairPosY;

    int step1Y, step2Y, step3Y, step4Y;
    int step1X, step2X, step3X, step4X;

    QRect *rect;
    QRect *rectPlat;

public:
    LevelBase(QWidget *parent);
    ~LevelBase();
    void drawLevel(QPainter &painter);
    void drawLevelBase(QPainter &painter);
    void drawPlatform(QPainter &painter);
    void drawStairs(QPainter &painter);

    void setPlatformPosX(int x);
    void setStairPosX(int x);
    int getStairPosX();
    int getPlatformPosX();
    int getPlatformPosY();
    int getPlatformEnd();
    int getStep1PosX();
    int getStep2PosX();
    int getStep3PosX();
    int getStep4PosX();

    int getStep1PosY();
    int getStep2PosY();
    int getStep3PosY();
    int getStep4PosY();

};

#endif // LEVELBASE_H
