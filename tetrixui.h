#pragma once

#include <QFrame>
#include <QWidget>
//#include "ui_tetrixui.h"

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
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
