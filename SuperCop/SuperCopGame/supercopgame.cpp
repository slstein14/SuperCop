#include "supercopgame.h"
#include "player.h"
#include <QGraphicsScene>
#include <QQmlComponent>
#include <QGraphicsObject>
#include <QKeyEvent>
#include <QDebug>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;



SuperCopGame::SuperCopGame(QWidget *parent) :
    QWidget(parent)
{
    srand(time(0));
    player = new Player(this);
    lb = new LevelBase(this);

    //Sets the Game Background (Currently Temporary)
    QPixmap bkgnd("../SuperCop/Images/background_temp.jpg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);

    timer = new QTimer();
    timer->setInterval(40);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateField()));
    timer->start();

    keyTimer = new QTimer();
    keyTimer->setInterval(5);
    connect(keyTimer, SIGNAL(timeout()), this, SLOT(pollKey()));
    keyTimer->start();

    isUpPressed = false;
    isDownPressed = false;
    isLeftPressed = false;
    isRightPressed = false;

    lastKeyPress = 0;
    gravity = 8; //pixels/s^2
}


SuperCopGame::~SuperCopGame()
{
    delete timer;
    delete player;
    delete keyTimer;
}


void SuperCopGame::keyPressEvent(QKeyEvent *evt)
{
    switch(evt->key())
    {
    case Qt::Key_Right:
        isRightPressed = true;
        break;
    case Qt::Key_Down:
        isDownPressed = true;
//        gamescore++;
        break;
    case Qt::Key_Up:
        isUpPressed = true;
        break;
    case Qt::Key_Left:
        isLeftPressed = true;
        break;
    default:
        break;
    }
}


void SuperCopGame::keyReleaseEvent(QKeyEvent *evt)
{
    switch(evt->key())
    {
    case Qt::Key_Right:
        isRightPressed = false;
        break;
    case Qt::Key_Down:
        isDownPressed = false;
        break;
    case Qt::Key_Up:
        isUpPressed = false;
        break;
    case Qt::Key_Left:
        isLeftPressed = false;
        break;
    default:
        break;
    }
}


void SuperCopGame::setLastKeyPress(int key)
{
    this->lastKeyPress = key;
}

void SuperCopGame::setPlatformX(int x)
{
    lb->setPlatformPosX(x);
}

void SuperCopGame::obstacleMovement()
{
    if((1 == player->getPlayerDirection()) && (player->getPosX() + player->getSizeX()) >= player->getRightBound())
    {
        lb->setPlatformPosX(lb->getPlatformPosX() - 5);
        lb->setStairPosX(lb->getStairPosX() - 5);
    }

    if((-1 == player->getPlayerDirection()) && (player->getPosX() <= player->getLeftBound()))
    {
        lb->setPlatformPosX(lb->getPlatformPosX() + 5);
        lb->setStairPosX(lb->getStairPosX() + 5);
    }
}

void SuperCopGame::physics()
{
    if (player->getPosY() < lb->getPlatformPosY())
    {
        if((player->getPosX() >= lb->getPlatformPosX()) && (player->getPosX() <= lb->getPlatformEnd()))
        {
            player->setCollided(true);
            player->setPosY(lb->getPlatformPosY() - 43);
        }
        else
        {
            player->setCollided(false);
            delPx = lb->getPlatformPosY() - player->getGround();
            speedYFinal = static_cast<int>(sqrt(2*gravity*delPx));
            fallTime = speedYFinal / gravity;
            player->setPosY(player->getGround() - 0.5*gravity*(fallTime * fallTime));
        }
    }

    if((player->getPosY() < player->getGround()) && (!player->isCollided()))
    {
        player->setCollided(false);
        delPx = player->getPosY() - player->getGround();
        speedYFinal = static_cast<int>(sqrt(2 * gravity * (player->getPosY() - player->getGround())));
        fallTime = speedYFinal / gravity;
        player->setPosY(player->getGround() - 0.5*gravity*(fallTime * fallTime));
    }
}

int SuperCopGame::getPlatformX()
{
    return lb->getPlatformPosX();
}


void SuperCopGame::pollKey() //DO NOT MODIFY. Code Works now.
{
    //Checks if any of the keys are pressed.
    if(isDownPressed)
        lastKeyPress = 3;
    else if(isUpPressed)
        lastKeyPress = 2;
    else if(isRightPressed)
        lastKeyPress = 1;
    else if(isLeftPressed )
        lastKeyPress = 4;
    else
    {
        //Checks if none of the keys are pressed before checking if some of the keys are pressed.
        if(!isUpPressed && !isDownPressed && !isLeftPressed && !isRightPressed)
        {
            if(3 == lastKeyPress && player->isRolling())
                lastKeyPress = 3;
            else if(2 == lastKeyPress && player->isJumping())
                lastKeyPress = 2;
            else if(1 == lastKeyPress && player->isMoveRight())
                lastKeyPress = 1;
            else if (4 == lastKeyPress && player->isMoveLeft())
                lastKeyPress = 4;
            else
                lastKeyPress = 0;
        }
        else
            lastKeyPress = 0;
    }
}


void SuperCopGame::updateField()
{
    player->playerAction(lastKeyPress);
    obstacleMovement();
    physics();
    this->update();
}


void SuperCopGame::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    player->drawPlayer(painter);
    lb->drawLevel(painter);

    //For debugging purposes
    QPen pen = QPen(Qt::red);
    painter.setPen(pen);
    painter.drawText(10, 10, QString("Frame: %1").arg(QString::number(player->getFrame())));
    painter.drawText(10, 20, QString("LastKeyPress: %1").arg(QString::number(lastKeyPress)));

    gamescore++;
    if(picX == player->getPosX())
    {
        timer->stop();
        QMessageBox mbox;
        mbox.setText("Game Over");
        mbox.exec();
        ifstream scoreset;
        scoreset.open("../SuperCop/highscores.txt");
        int scores;

        if(scoreset.is_open()){

            scoreset >> scores;
            int firstscore = scores;
            scoreset >> scores;
            int secondscore = scores;
            scoreset >> scores;
            int thirdscore = scores;
            scoreset >> scores;
            int fourthscore = scores;
            scoreset >> scores;
            int fifthscore = scores;
            scoreset.close();

            if(firstscore < gamescore)
            {
                   fifthscore = fourthscore;
                   fourthscore = thirdscore;
                   thirdscore = secondscore;
                   secondscore = firstscore;
                   firstscore = gamescore;
            //maybe add a window which declares "New High Score" in this case-time permitting
            }
            else if(secondscore < gamescore)
            {
                   fifthscore = fourthscore;
                   fourthscore = thirdscore;
                   thirdscore = secondscore;
                   secondscore = gamescore;
            }
            else if(thirdscore < gamescore)
            {
                   fifthscore = fourthscore;
                   fourthscore = thirdscore;
                   thirdscore = gamescore;
            }
            else if(fourthscore < gamescore)
            {
                   fifthscore = fourthscore;
                   fourthscore = gamescore;
            }
            else if(fifthscore<gamescore)
            {
                   fifthscore = gamescore;
            }

            ofstream setscores;
            setscores.open("../SuperCop/highscores.txt");

            setscores << firstscore << endl;
            setscores << secondscore << endl;
            setscores << thirdscore << endl;
            setscores << fourthscore << endl;
            setscores << fifthscore << endl;

            setscores.close();
            }//resets high scores if new high score acheived

         }
    }

