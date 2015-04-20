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

};

#endif // LEVELBASE_H
