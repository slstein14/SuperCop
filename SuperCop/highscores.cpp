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
    scoreset.open("../SuperCop/highscores1.txt");
    int scores;
    if(scoreset.is_open()){
       scoreset>>scores;
       ui->Score1_1->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score1_2->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score1_3->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score1_4->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score1_5->setText(QString::number(scores));
    }//reads current high scores
    scoreset.close();

    scoreset.open("../SuperCop/highscores2.txt");
    if(scoreset.is_open()){
       scoreset>>scores;
       ui->Score2_1->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score2_2->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score2_3->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score2_4->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score2_5->setText(QString::number(scores));
    }//reads current high scores
    scoreset.close();

    scoreset.open("../SuperCop/highscores3.txt");
    if(scoreset.is_open()){
       scoreset>>scores;
       ui->Score3_1->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score3_2->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score3_3->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score3_4->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score3_5->setText(QString::number(scores));
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
    reset.open("../SuperCop/highscores1.txt");
    for(int i=0;i<5;i++){
    reset<<0<<endl;
    }
    reset.close();

    reset.open("../SuperCop/highscores2.txt");
    for(int i=0;i<5;i++){
    reset<<0<<endl;
    }
    reset.close();

    reset.open("../SuperCop/highscores3.txt");
    for(int i=0;i<5;i++){
    reset<<0<<endl;
    }
    reset.close();

    ifstream scoreset;
    scoreset.open("../SuperCop/highscores1.txt");
    int scores;
    if(scoreset.is_open()){
       scoreset>>scores;
       ui->Score1_1->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score1_2->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score1_3->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score1_4->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score1_5->setText(QString::number(scores));
    }

    scoreset.open("../SuperCop/highscores2.txt");
    if(scoreset.is_open()){
       scoreset>>scores;
       ui->Score2_1->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score2_2->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score2_3->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score2_4->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score2_5->setText(QString::number(scores));
    }//reads current high scores
    scoreset.close();

    scoreset.open("../SuperCop/highscores3.txt");
    if(scoreset.is_open()){
       scoreset>>scores;
       ui->Score3_1->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score3_2->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score3_3->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score3_4->setText(QString::number(scores));
       scoreset>>scores;
       ui->Score3_5->setText(QString::number(scores));
    }//reads current high scores
    scoreset.close();


}//Resets the High Scores

