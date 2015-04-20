#ifndef ENEMY_H
#define ENEMY_H

#include <QPainter>
#include <QPixmap>
#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QKeyEvent>

class Enemy
{
public:
    Enemy(QWidget *parent);
    ~Enemy();

    void drawEnemy(QPainter &painter);
    void changeImage(QString str);

    void setPosX(int x);
    void setPosY(int y);
    void setSizeX(int x);
    void setSizeY(int y);
    void setSpeed(int speed);

    int getPosX();
    int getPosY();
    int getSizeX();
    int getSizeY();
    int getSpeed();

private:
    int speed;
    int posX;
    int posY;
    int sizeX;
    int sizeY;
    int frame;
    QPixmap *robot;
    QTimer *moveTimer;
};

#endif // ENEMY_H
