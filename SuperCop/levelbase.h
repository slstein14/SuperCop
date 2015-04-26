#ifndef LEVELBASE_H
#define LEVELBASE_H

#include <QPainter>
#include <QWidget>
#include <QRect>
#include <QTimer>
//#include "platform.h"


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
    int stairPosX, stairPosY;

    int step1Y, step2Y, step3Y, step4Y;
    int step1X, step2X, step3X, step4X;

    QRect *rect;
    QTimer *generateLevel;

public:
    LevelBase(QWidget *parent);
    ~LevelBase();
    void drawLevel(QPainter &painter);
    void drawLevelBase(QPainter &painter);
    void drawStairs(QPainter &painter);
    void drawLevel();

    void setStairPosX(int x);
    int getStairPosX();

    int getStep1PosX();
    int getStep2PosX();
    int getStep3PosX();
    int getStep4PosX();

    int getStep1PosY();
    int getStep2PosY();
    int getStep3PosY();
    int getStep4PosY();

public slots:
    void generatePiece();

};

#endif // LEVELBASE_H
