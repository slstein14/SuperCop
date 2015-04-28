//Alex Portolese and Sam Stein
//This file contains the declarations for the Main window.
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "contactus.h"
#include "controls.h"
#include "highscores.h"
#include "supercopgame.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionContact_Us_triggered();

    void on_actionControls_triggered();

    void on_actionHigh_Scores_triggered();

    void on_Easy_1P_triggered();

    void on_Medium_1P_triggered();

    void on_Hard_1P_triggered();

    void on_easy_clicked();

    void on_medium_clicked();

    void on_hard_clicked();

    void on_highscores_clicked();

    void on_exit_clicked();

private:
    Ui::MainWindow *ui;
    ContactUs* contact;
    Controls* controls;
    HighScores* hScore;
    SuperCopGame *scg;
};

#endif // MAINWINDOW_H
