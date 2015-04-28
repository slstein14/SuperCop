//Alex Portolese and Sam Stein
//This file contains the coding to make the classes interact in the game.

#include "supercopgame.h"
#include "player.h"
#include <QKeyEvent>
#include <QDebug>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <donut.h>
#include <QRect>

using namespace std;

SuperCopGame::SuperCopGame(QWidget *parent) :
    QWidget(parent)
{
    QWidget::setFixedSize(this->width(),this->height());
    player = new Player(this);
    lb = new LevelBase(this);
    msg = new QMessageBox();

    //Sets the Game Background (Currently Temporary)
    QPixmap bkgnd("../SuperCop/Images/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    timer = new QTimer();
    timer->setInterval(50);
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
    gamescore=0;
    location=0;
    this->setVecs();
}//Initializes game variables


SuperCopGame::~SuperCopGame()
{
    delete timer;
    delete player;
    delete keyTimer;

    for(unsigned int i=0;i<enemyspawn.size();i++){
        delete enemies.at(i);
    }
    enemies.clear();
    enemyspawn.clear();

    for(unsigned int i=0;i<donutspawn.size();i++){
        delete donuts.at(i);
    }
    donuts.clear();
    donutspawn.clear();

    for(unsigned int i = 0; i < wallSpawn.size(); i++)
    {
        delete walls.at(i);
    }
    walls.clear();
    wallSpawn.clear();

    for(unsigned int i = 0; i < platSpawn.size(); i++)
    {
        delete platforms.at(i);
    }
    platforms.clear();
    platSpawn.clear();

    delete levelEnd;

    for(unsigned int i=0;i<wallSpawn.size();i++){
        delete walls.at(i);
    }
    walls.clear();
    wallSpawn.clear();

    for(unsigned int i=0;i<platSpawn.size();i++){
        delete platforms.at(i);
    }
    platforms.clear();
    platSpawn.clear();

}//Destructor


void SuperCopGame::keyPressEvent(QKeyEvent *evt)
{
    switch(evt->key())
    {
    case Qt::Key_Right:
        isRightPressed = true;
        break;
    case Qt::Key_Down:
        isDownPressed = true;
        break;
    case Qt::Key_Up:
        isUpPressed = true;
        break;
    case Qt::Key_Left:
        isLeftPressed = true;
        break;
    case Qt::Key_Escape:
        msg->setText("Paused");
        msg->exec();
        break;
    case Qt::Key_P:
        msg->setText("Paused");
        msg->exec();
        break;
    default:
        break;
    }
}//Reads user key presses

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
}//Reads user Key Releases


void SuperCopGame::setLastKeyPress(int key)
{
    this->lastKeyPress = key;
}//Sets key based on key presses


void SuperCopGame::obstacleMovement()
{
    for(unsigned int i = 0; i < enemies.size(); i++)
    {
        if((*(enemies.at(i))).getActive())
        {
            if(1 == (*(enemies.at(i))).getDirection())
            {
                (*(enemies.at(i))).setPosX((*(enemies.at(i))).getPosX() - moveSpeed - 3);
            }
            else if (0 == (*(enemies.at(i))).getDirection())
            {
                (*(enemies.at(i))).setPosX((*(enemies.at(i))).getPosX() + moveSpeed + 3);
            }
        }//enemy moves based on time
    }
    if((1 == lastKeyPress || 2 == lastKeyPress) && (player->getPosX() + player->getSizeX()) >= player->getRightBound()&& levelEnd->getPosX() >= 0)
    {
        for(unsigned int i = 0; i < platforms.size(); i++)
        {
            if((*(platforms.at(i))).isActive())
            {
                (*(platforms.at(i))).setPlatformPosX((*(platforms.at(i))).getPlatformPosX() - moveSpeed);
            }
        }//Platforms scroll

        for(unsigned int i = 0; i < walls.size(); i++)
        {
            if((*(walls.at(i))).isActive())
            {
                (*(walls.at(i))).setWallPosX((*(walls.at(i))).getWallPosX() - moveSpeed);
            }
        }//Walls scroll

        for(unsigned int i = 0; i < donuts.size(); i++)
        {
            if((*(donuts.at(i))).getActive()){
                (*(donuts.at(i))).setPosX((*(donuts.at(i))).getPosX() - moveSpeed);
            }
        }//Donuts scroll

        location+=(moveSpeed/5);
        levelEnd->setPosX(levelEnd->getPosX() - moveSpeed);
    }

    if((4 == lastKeyPress || 2 == lastKeyPress) && (player->getPosX() <= player->getLeftBound())&&0<location)
    {
        for(unsigned int i = 0; i < platforms.size(); i++)
        {
            if((*(platforms.at(i))).isActive())
            {
                (*(platforms.at(i))).setPlatformPosX((*(platforms.at(i))).getPlatformPosX() + moveSpeed);
            }
        }//Platforms scroll

        for(unsigned int i = 0; i < walls.size(); i++)
        {
            if((*(walls.at(i))).isActive())
            {
                (*(walls.at(i))).setWallPosX((*(walls.at(i))).getWallPosX() + moveSpeed);
            }
        }//Walls scroll

        for(unsigned int i=0;i<donuts.size();i++)
        {
            if((*(donuts.at(i))).getActive())
            {
                (*(donuts.at(i))).setPosX((*(donuts.at(i))).getPosX() + moveSpeed);
            }
        }//Donuts scroll

        for(unsigned int i = 0; i < enemies.size(); i++)
        {
            if((*(enemies.at(i))).getActive())
            {
                (*(enemies.at(i))).setPosX((*(enemies.at(i))).getPosX() + moveSpeed - 2);
            }
        }//enemies appear to move slower when the player runs away

        location-=(moveSpeed/5);
        levelEnd->setPosX(levelEnd->getPosX() + moveSpeed);
    }
}//Scrolls objects across the screen as necessary


void SuperCopGame::pollKey() //DO NOT MODIFY
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
}//Checks which key is being pressed, stops animation loops


void SuperCopGame::updateField()
{
    player->playerAction(lastKeyPress);
    obstacleMovement();
    this->update();
}//Updates the painted locations of objects based on a timer

void SuperCopGame::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    player->drawPlayer(painter);
    lb->drawLevelBase(painter);

    //===========================================================
    //    START PHYSICS
    //===========================================================
    QRect enemyRect, playerRect, donutRect, levelEndRect, platRect, wallRect;
    playerRect = QRect(player->getPosX(),player->getPosY(),player->getSizeX(),player->getSizeY());

    for(unsigned int i = 0; i < donuts.size(); i++)
    {
        donutRect = QRect((*(donuts.at(i))).getPosX(),(*(donuts.at(i))).getPosY(),(*(donuts.at(i))).getSizeX(),(*(donuts.at(i))).getSizeY());

        if(donutspawn.at(i)==location)
        {
            (*(donuts.at(i))).setActive(true);
        }//spawns a donut at each read location

        if((*(donuts.at(i))).getActive())
        {
            (*(donuts.at(i))).drawDonut(painter);
        }//Controls whether donut is painted

        if((*(donuts.at(i))).getActive() && playerRect.intersects(donutRect)){
            (*(donuts.at(i))).setActive(false);
            (*(donuts.at(i))).setPosX(-10000);//Donuts may technically be reactivated by going backward, but the player cannot go back past 0, and donuts will spawn waaaay back.
            gamescore+=10;
        }//handles collisions with donut

        for(unsigned int j = 0; j < walls.size(); j++){

            wallRect = QRect((*(walls.at(j))).getWallPosX(),(*(walls.at(j))).getWallPosY(),(*(walls.at(j))).getWallSizeX(),(*(walls.at(j))).getWallSizeY());
            if(donutRect.intersects(wallRect)){
                (*(donuts.at(i))).setActive(false);
            }
        }//Donuts don't spawn in walls
    }//Handles all cases of donut objects.

    for(unsigned int i = 0; i < enemies.size(); i++)
    {
        enemyRect = QRect((*(enemies.at(i))).getPosX(),(*(enemies.at(i))).getPosY(),(*(enemies.at(i))).getSizeX(),(*(enemies.at(i))).getSizeY());

        for(unsigned int j = 0; j < walls.size(); j++)
        {
            wallRect = QRect((*(walls.at(j))).getWallPosX(),(*(walls.at(j))).getWallPosY(),(*(walls.at(j))).getWallSizeX(),(*(walls.at(j))).getWallSizeY());

            if(enemyRect.intersects(wallRect) && (*(walls.at(j))).isActive())
            {
                switch((*(enemies.at(i))).getDirection())
                {
                case 0:
                    (*(enemies.at(i))).setDirection(1);
                    break;
                case 1:
                    (*(enemies.at(i))).setDirection(0);
                    break;
                }
            }
        }//Enemies turn around when they hit walls

        if (0 == (*(enemies.at(i))).getDirection()&&this->width()==(*(enemies.at(i))).getPosX()){
            (*(enemies.at(i))).setDirection(1);
        }//Enemies don't wander off the right side of the screen


        if(enemyspawn.at(i) == location)
        {
            (*(enemies.at(i))).setActive(true);
        }//spawns an enemy at each read location

        if((*(enemies.at(i))).getActive())
        {
            (*(enemies.at(i))).drawEnemy(painter);
        }//enemy moves based on time

        if(playerRect.intersects(enemyRect) && player->isJumping() && !player->isAscending())
        {
            (*(enemies.at(i))).setActive(false);
            (*(enemies.at(i))).setPosX(-100);
        }//Kills enemy if you jump on it

        if(playerRect.intersects(enemyRect) && (player->isOnGround() || player->isAscending()))
        {
            (*(enemies.at(i))).setPosY((*(enemies.at(i))).getPosY() - 1);
            timer->stop();
            msg->setText("Game Over");
            msg->exec();
            this->setHighScores();
            this->close();
        }//Handles game-ending collisions
    }//Handles all cases of enemy objects.

    for(unsigned int i = 0; i < walls.size(); i++)
    {
        wallRect = QRect((*(walls.at(i))).getWallPosX(), (*(walls.at(i))).getWallPosY(), (*(walls.at(i))).getWallSizeX(), (*(walls.at(i))).getWallSizeY());

        if(wallSpawn.at(i) == location)
        {
            (*(walls.at(i))).setActive(true);
        }//Spawns a wall at each read location

        if((*walls.at(i)).isActive())
        {
            (*(walls.at(i))).drawWall(painter);
        }//Controls whether wall is drawn on screen

    }//Handles all wall objects

    for(unsigned int i = 0; i < platforms.size(); i++)
    {
        platRect = QRect((*(platforms.at(i))).getPlatformPosX(), (*(platforms.at(i))).getPlatformPosY(), (*(platforms.at(i))).getPlatformSizeX(), (*(platforms.at(i))).getPlatformSizeY());

        if(platSpawn.at(i) == location)
        {
            (*(platforms.at(i))).setActive(true);
        }//Spawns platform of each read location

        if((*platforms.at(i)).isActive())
        {
            (*(platforms.at(i))).drawPlatform(painter);
        }//Controls whether wall is drawn on screen

        if(playerRect.intersects(platRect) && (player->getPosY() < 315) && !player->isAscending())
        {
            player->setPosY(270);
            player->setJumping(false);
            player->setOnPlatform(true);
            player->setOnWall(false);
            player->setOnGround(false);
        }
    }//handles all platform objects

    if(playerRect.intersects(platRect) && (player->getPosY() < 315) && !player->isAscending())
    {
        player->setPosY(270);
        player->setJumping(false);
        player->setOnPlatform(true);
        player->setOnWall(false);
        player->setOnGround(false);
    }//Platform Collision handler

    for(unsigned int i=0;i<walls.size();i++)
    {
        wallRect = QRect((*(walls.at(i))).getWallPosX(),(*(walls.at(i))).getWallPosY(),(*(walls.at(i))).getWallSizeX(),(*(walls.at(i))).getWallSizeY());

        if(wallSpawn.at(i)==location){
            (*(walls.at(i))).setActive(true);
        }//spawns a wall at each read location

        if((*(walls.at(i))).isActive())
        {
            (*(walls.at(i))).drawWall(painter);
        }//Controls whether wall is painted

        if(playerRect.intersects(wallRect) && (player->getPosY() < 340) && !player->isAscending())
        {
            player->setPosY(290);
            player->setJumping(false);
            player->setOnPlatform(false);
            player->setOnWall(true);
            player->setOnGround(false);
        }
    }//Wall Collison handler

    if((player->getPosY() >= player->getGround()) && !player->isAscending() && !player->isOnWall() && !player->isOnPlatform())
    {
        player->setPosY(player->getGround());
        player->setJumping(false);
        player->setOnPlatform(false);
        player->setOnWall(false);
        player->setOnGround(true);
    }//Ground Collision handler
    else
    {
        player->setPosY(player->getPosY() + 10);
        //        player->setJumping(true);
        player->setOnPlatform(false);
        player->setOnWall(false);
        player->setOnGround(false);
    }//Lowers Player until collision occurs

    for(unsigned int i=0;i<walls.size();i++)
    {
        wallRect = QRect((*(walls.at(i))).getWallPosX(),(*(walls.at(i))).getWallPosY(),(*(walls.at(i))).getWallSizeX(),(*(walls.at(i))).getWallSizeY());

        if((player->getPosY() + 40 > (*(walls.at(i))).getWallPosY()) && (playerRect.intersects(wallRect)) && (1 == player->getPlayerDirection()))
        {
            player->setPosX((*(walls.at(i))).getWallPosX() - player->getSizeX() );
            player->setWallCollided(true);
        }//Checks for player colliding with the left side of a wall
        else if((player->getPosY() + 40 > (*(walls.at(i))).getWallPosY()) && (playerRect.intersects(wallRect)) && (-1 == player->getPlayerDirection()))
        {
            player->setPosX((*(walls.at(i))).getWallPosX()+(*(walls.at(i))).getWallSizeX());
            player->setWallCollided(true);
        }//Checks for player colliding with the left side of a wall
        else
        {
            player->setWallCollided(false);
        }//Sets flag for when player is not colliding with a wall
    }

    //===========================================================
    //    END PHYSICS
    //===========================================================

    //START DEBUG ITEMS

    QPen pen = QPen(Qt::white);
    painter.setPen(pen);
    painter.drawText(10, 10, QString("Score: %1").arg(QString::number(gamescore)));

    levelEnd->drawDonut(painter);
    levelEndRect = QRect(levelEnd->getPosX(),levelEnd->getPosY(),levelEnd->getSizeX(),levelEnd->getSizeY());

    if(playerRect.intersects(levelEndRect))
    {
        gamescore += 100;
        timer->stop();
        player->setPosX(player->getPosX() + 1);
        msg->setText("Level Beaten");
        msg->exec();
    }//Handles game winning scenario

}//Handles Painting all elements on screen


void SuperCopGame::setVecs(){
    QString enemyfile("../SuperCop/level/enemy.txt");
    QString donutfile("../SuperCop/level/donut.txt");
    QString wallFile("../SuperCop/level/wall.txt");
    QString platFile("../SuperCop/level/platform.txt");

    ifstream enemyread;
    enemyread.open(enemyfile.toStdString().c_str());
    int enemynum;
    if(enemyread.is_open())
    {
        while(enemyread>>enemynum)
        {
            enemyspawn.push_back(enemynum);
        }
    }
    enemyread.close();

    for(unsigned int i = 0; i < enemyspawn.size(); i++)
    {
        Enemy *enemy;
        enemy = new Enemy(this);
        enemies.push_back(enemy);
    }//Enemy Vector initialization

    ifstream donutread;
    donutread.open(donutfile.toStdString().c_str());
    int donutnum;
    if(donutread.is_open())
    {
        while(donutread >> donutnum)
        {
            donutspawn.push_back(donutnum);
        }
    }
    donutread.close();

    for(unsigned int i = 0; i < donutspawn.size(); i++)
    {
        Donut *donut;
        donut= new Donut(this);
        donuts.push_back(donut);
    }//Donut Vector Initialization

    ifstream wallRead;
    wallRead.open(wallFile.toStdString().c_str());
    int wallNum;
    if(wallRead.is_open())
    {
        while(wallRead >> wallNum)
        {
            wallSpawn.push_back(wallNum);
        }
    }
    wallRead.close();

    for(unsigned int i = 0; i < wallSpawn.size(); i++)
    {
        Wall *wall;
        wall = new Wall(this);
        walls.push_back(wall);
    }//Wall Vector Initialization

    ifstream platRead;
    platRead.open(platFile.toStdString().c_str());
    int platNum;
    if(platRead.is_open())
    {
        while(platRead >> platNum)
        {
            platSpawn.push_back(platNum);
        }
    }
    platRead.close();

    for(unsigned int i = 0; i < platSpawn.size(); i ++)
    {
        Platform *plat;
        plat = new Platform(this);
        platforms.push_back(plat);
    }//Platform Vector Initialization

    levelEnd = new Donut(this);
    levelEnd->setSizeX(40);
    levelEnd->setSizeY(40);
    levelEnd->setPosX(6500);
    levelEnd->setPosY(this->height()-200);
    //Initializes game ending Donut

}//Initializes vectors


void SuperCopGame::setHighScores(){
    int scorefile = moveSpeed / 5;
    QString filename = "../SuperCop/highscores"+QString::number(scorefile)+".txt";
    ifstream scoreset;
    scoreset.open(filename.toStdString().c_str());
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

            QMessageBox sbox;
            sbox.setText("New High Score: "+ QString::number(gamescore));
            sbox.exec();
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
        setscores.open(filename.toStdString().c_str());

        setscores << firstscore << endl;
        setscores << secondscore << endl;
        setscores << thirdscore << endl;
        setscores << fourthscore << endl;
        setscores << fifthscore << endl;

        setscores.close();
    }
}//resets high scores if new high score acheived


void SuperCopGame::setMoveSpeed(int spd)
{
    moveSpeed = spd;
    player->setSpeedX(spd);
}//set movement speed;
