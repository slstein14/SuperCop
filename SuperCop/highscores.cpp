//Alex Portolese and Sam Stein
//This file contains the coding to make the High Scores window run and update properly.
#include "highscores.h"
#include "ui_highscores.h"
#include <fstream>
using namespace std;

HighScores::HighScores(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HighScores)
{
    ui->setupUi(this);
    ifstream scoreset;
    scoreset.open("../SuperCop/highscores.txt");
    int scores;
    if(scoreset.is_open()){
       scoreset>>scores;
       ui->Score1->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score2->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score3->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score4->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score5->setText(QString::number(scores));
    }//reads current high scores
scoreset.close();

}//Runs High Score Window

HighScores::~HighScores()
{
    delete ui;
}//clears potential memory leaks

void HighScores::on_reset_clicked()
{
    ofstream reset;
    reset.open("../SuperCop/highscores.txt");
    for(int i=0;i<5;i++){
    reset<<0<<endl;
    }
    reset.close();

    ifstream scoreset;
    scoreset.open("../SuperCop/highscores.txt");
    int scores;
    if(scoreset.is_open()){
       scoreset>>scores;
       ui->Score1->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score2->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score3->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score4->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score5->setText(QString::number(scores));
    }
}//Resets the High Scores

