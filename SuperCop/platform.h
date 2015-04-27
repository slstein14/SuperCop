#ifndef PLATFORM_H
#define PLATFORM_H

#include <QPainter>
#include <QWidget>
#include <QRect>


class Platform
{
private:
    QPixmap *platform;
    QRect *rectPlat;
    int picX, picY;
    int platformHeight, platformPosX, platformLength;
    int gameWindow;
    bool active;

public:
    Platform(QWidget *parent = 0);
    ~Platform();

    void drawPlatform(QPainter &painter);
    void setPlatformPosX(int x);
    void setActive(bool active);

    int getPlatformPosX();
    int getPlatformPosY();
    int getPlatformEnd();
    int getPlatformSizeX();
    int getPlatformSizeY();
    bool isActive();
};

#endif // PLATFORM_H
