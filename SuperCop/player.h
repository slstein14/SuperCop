#ifndef Player_H
#define Player_H

#include <QPainter>
#include <QPixmap>
#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QKeyEvent>

class Player : public QObject
{

private:
    enum keyPressed {NONE = 0, RIGHT = 1, UP = 2, DOWN = 3, LEFT = 4};

    int posX;
    int posY;
    int sizeX;
    int sizeY;
    int frame;
    int lastActionPressed;
    QPixmap *image;
    QTimer *animationTimer;

public:

    Player(QWidget *parent);
    ~Player();

    void drawPlayer(QPainter &painter);
    void changeImage(QString str);
    void playerScreenPos(QWidget *w);

    int jump();
    int roll();
    int run();
    int runInverted();
    void standBy();

    void setPosX(int x);
    void setPosY(int y);
    void setSizeX(int x);
    void setSizeY(int y);

    int getPosX();
    int getPosY();
    int getSizeX();
    int getSizeY();

public slots:
    int playerAction(int action);
};

#endif // Player_H
