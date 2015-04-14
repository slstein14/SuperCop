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

SuperCopGame::SuperCopGame(QWidget *parent) :parent(parent)

{
    srand(time(0));
    player = new Player(this);
    QPixmap bkgnd("../SuperCop/Images/background_temp.jpg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);

    timer = new QTimer();
    timer->setInterval(40);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateField()));
    timer->start();
   robot = new QPixmap("../SuperCop/Images/robot.png");
    lastKeyPress = 1;
    gamescore=0;
    picX=600;
    picY=250;
    picHeight = 100;
    picWidth = 100;
}

SuperCopGame::~SuperCopGame()
{
    delete timer;
    delete player;
}

void SuperCopGame::keyPressEvent(QKeyEvent *evt)
{
    switch(evt->key())
    {
    case Qt::Key_Right:
        qDebug() << "Right";
        lastKeyPress = 1;
        break;
    case Qt::Key_Down:
        qDebug() << "Down";
        lastKeyPress = 3;
        gamescore++;
        break;
    case Qt::Key_Up:
        qDebug() << "Up";
        lastKeyPress = 2;
        break;
    case Qt::Key_Left:
        qDebug() << "Left";
        lastKeyPress = 4;
        break;
    }

}

void SuperCopGame::setLastKeyPress(int key)
{
    this->lastKeyPress = key;
}

void SuperCopGame::updateField()
{
    if(0 == player->playerAction(lastKeyPress))
        setLastKeyPress(0);
    else
        player->playerAction(lastKeyPress);

    this->update();
}

void SuperCopGame::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    player->drawPlayer(painter);
    painter.drawPixmap(picX,picY,picWidth,picHeight,*robot);
    picX-=5;
    gamescore++;
    if(picX==player->getPosX()){
        timer->stop();
        QMessageBox mbox;
        mbox.setText("Game Over");
        mbox.exec();
        ifstream scoreset;
        scoreset.open("../SuperCop/highscores.txt");
        int scores;

        if(scoreset.is_open()){

            scoreset>>scores;
            int firstscore=scores;
            scoreset>>scores;
            int secondscore=scores;
            scoreset>>scores;
            int thirdscore=scores;
            scoreset>>scores;
            int fourthscore=scores;
            scoreset>>scores;
            int fifthscore=scores;
            scoreset.close();

            if(firstscore<gamescore){
                   fifthscore=fourthscore;
                   fourthscore=thirdscore;
                   thirdscore=secondscore;
                   secondscore=firstscore;
                   firstscore=gamescore;
           //maybe add a window which declares "New High Score" in this case-time permitting
            }
            else if(secondscore<gamescore){
                   fifthscore=fourthscore;
                   fourthscore=thirdscore;
                   thirdscore=secondscore;
                   secondscore=gamescore;
            }
            else if(thirdscore<gamescore){
                   fifthscore=fourthscore;
                   fourthscore=thirdscore;
                   thirdscore=gamescore;
            }
            else if(fourthscore<gamescore){
                   fifthscore=fourthscore;
                   fourthscore=gamescore;
            }
            else if(fifthscore<gamescore){
                   fifthscore=gamescore;
            }

            ofstream setscores;
            setscores.open("../SuperCop/highscores.txt");

            setscores<<firstscore<<endl;
            setscores<<secondscore<<endl;
            setscores<<thirdscore<<endl;
            setscores<<fourthscore<<endl;
            setscores<<fifthscore<<endl;

            setscores.close();
            }//resets high scores if new high score acheived

         }
    }

