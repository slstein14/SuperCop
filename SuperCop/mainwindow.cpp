//Alex Portolese and Sam Stein
//This file contains the coding to make the Main window run and update properly,
//and to make the menus accessible to the user.
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("../SuperCop/Images/SuperCop.png");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
        contact = NULL;
        controls = NULL;
        hScore = NULL;
        scg = NULL;

}//Sets the background image for the main menu

MainWindow::~MainWindow()
{
    delete ui;
    delete contact;
    delete controls;
    delete hScore;
    delete scg;
}//Clears potential memory leaks

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}//Exits the program

void MainWindow::on_actionContact_Us_triggered()
{
    if(contact==NULL){
        contact = new ContactUs();
    }
    contact->show();
}//Opens an instance of the Contact Us window

void MainWindow::on_actionControls_triggered()
{
    if(controls==NULL){
        controls = new Controls();
    }
    controls->show();
}//Opens an instance of the Controls window

void MainWindow::on_actionHigh_Scores_triggered()
{
    if(hScore==NULL)
    {
        hScore = new HighScores();
    }else{
        delete hScore;
        hScore = new HighScores();
    }

    hScore->show();
}//Opens an instance of the High Score window

void MainWindow::on_Easy_1P_triggered()
{
    if(scg == NULL)
    {
        scg = new SuperCopGame();
        scg->setMoveSpeed(5);
    }else{
        delete scg;
        scg = new SuperCopGame();
        scg->setMoveSpeed(5);
    }
    scg->show();
}//Creates a 1 player game on easy

void MainWindow::on_Medium_1P_triggered()
{
    if(scg == NULL)
    {
        scg = new SuperCopGame();
        scg->setMoveSpeed(10);
    }else{
        delete scg;
        scg = new SuperCopGame();
        scg->setMoveSpeed(10);
     }
     scg->show();

}//Creates a 1 player game on medium

void MainWindow::on_Hard_1P_triggered()
{
    if(scg == NULL)
    {
        scg = new SuperCopGame();
        scg->setMoveSpeed(15);
    }else{
        delete scg;
        scg = new SuperCopGame();
        scg->setMoveSpeed(15);
    }
    scg->show();
}//Creates a 1 player game on hard
