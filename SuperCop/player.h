//Alex Portolese and Sam Stein
//This file contains the declarations for the Player class.
#ifndef Player_H
#define Player_H

#include <QPainter>
#include <QPixmap>
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>

class Player : QObject
{

private:
    enum keyPressed {NONE = 0, RIGHT = 1, UP = 2, DOWN = 3, LEFT = 4};
//    enum keyPress2 {W = UP, A = LEFT, S = DOWN, D = RIGHT};
    enum direction {WEST = -1, STAND = 0, EAST = 1};

    bool rolling, jumping, moveLeft, moveRight, ascend, upPressed;
    bool onGround, playerOnWall, playerOnPlatform;
    int posX, posY;
    int sizeX, sizeY;

    int frame;
    int leftBound, rightBound;
    int ground;

    int lastActionPressed;
    int playerDirection;

    QPixmap *image;

public:

    Player(QWidget *parent);
    ~Player();

    void drawPlayer(QPainter &painter);
    void changeImage(QString str);
    void playerScreenPos(QWidget *w);

    void jump();
    void roll();
    void run();
    void runInverted();
    void standBy();

    void setPosX(int x);
    void setPosY(int y);
    void setSizeX(int x);
    void setSizeY(int y);
    void setOnGround(bool onGround);
    void setSpeedY(int y);
    void setJumping(bool jump);
    void setOnWall(bool onWall);
    void setOnPlatform(bool onPlat);

    int getPosX();
    int getPosY();
    int getSizeX();
    int getSizeY();
    int getFrame();
    int getLeftBound();
    int getRightBound();
    int getPlayerDirection();
    int getGround();
    int getSpeedY();

    bool isRolling();
    bool isJumping();
    bool isMoveRight();
    bool isMoveLeft();
    bool isOnGround();
    bool isAscending();
    bool isOnPlatform();
    bool isOnWall();

public slots:
    void playerAction(int action);
};

#endif // Player_H
