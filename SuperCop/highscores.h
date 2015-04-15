//Alex Portolese and Sam Stein
//This file contains the declarations for the High Scores window.
#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <QWidget>

namespace Ui {
class HighScores;
}

class HighScores : public QWidget
{
    Q_OBJECT

public:
    explicit HighScores(QWidget *parent = 0);
    ~HighScores();

private slots:
    void on_reset_clicked();

private:
    Ui::HighScores *ui;
};

#endif // HIGHSCORES_H
