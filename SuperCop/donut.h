//Alex Portolese and Sam Stein
//This file contains the declarations for the Donut class.
#ifndef DONUT_H
#define DONUT_H

#include <QPainter>
#include <QPixmap>
#include <QWidget>
#include <QPixmap>
#include <QKeyEvent>

class Donut
{
public:
    Donut(QWidget *parent);
    ~Donut();

    void drawDonut(QPainter &painter);
    void changeImage(QString str);

    void setPosX(int x);
    void setPosY(int y);
    void setSizeX(int x);
    void setSizeY(int y);

    int getPosX();
    int getPosY();
    int getSizeX();
    int getSizeY();

    bool getActive();
    void setActive(bool act);

private:
    int windowwidth;
    int posX;
    int posY;
    int sizeX;
    int sizeY;
    QPixmap *donut;
    bool active;
};

#endif // DONUT_H
