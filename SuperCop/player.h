#ifndef Player_H
#define Player_H

#include <QPainter>
#include <QPixmap>
#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QKeyEvent>

class Player : QObject
{

private:
    enum keyPressed {NONE = 0, RIGHT = 1, UP = 2, DOWN = 3, LEFT = 4};
//    enum keyPress2 {W = UP, A = LEFT, S = DOWN, D = RIGHT};
    enum direction {WEST = -1, STAND = 0, EAST = 1};

    bool rolling, jumping, moveLeft, moveRight;
    bool collided;
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
    void setCollided(bool collided);
    void setSpeedY(int y);

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
    bool isCollided();

public slots:
    void playerAction(int action);
};

#endif // Player_H
