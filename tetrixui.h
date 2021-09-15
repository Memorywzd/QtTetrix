#pragma once



//#include "ui_tetrixui.h"

#include <qlcdnumber.h>
#include <qlabel.h>
#include <qpushbutton.h>
class TetrixLogic;

class TetrixUI : public QWidget
{
    Q_OBJECT

public:
    TetrixUI();

private:
    //Ui::TetrixUIClass ui;
    QLabel* createLabel(const QString& text);

    TetrixLogic* logic;
    QLabel* nextCubeLabel;
    QLCDNumber* scoreLcd;
    QLCDNumber* levelLcd;
    QLCDNumber* linesLcd;
    QPushButton* startButton;
    QPushButton* quitButton;
    QPushButton* pauseButton;
};
