//Alex Portolese and Sam Stein
//This file contains the declarations for the Level floor.
#ifndef LEVELBASE_H
#define LEVELBASE_H

#include <QPainter>
#include <QWidget>
#include <QRect>
#include <QTimer>

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
    QRect *rect;
    QTimer *generateLevel;

public:
    LevelBase(QWidget *parent);
    ~LevelBase();

    void drawLevelBase(QPainter &painter);

public slots:
    void generatePiece();
};

#endif // LEVELBASE_H
