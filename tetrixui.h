#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_tetrixui.h"

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class TetrixLogic;

class TetrixUI : public QMainWindow
{
    Q_OBJECT

public:
    TetrixUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::TetrixUIClass ui;

    QLabel* createLabel(const QString& text);

    TetrixLogic* logic;
    QLabel* nextPieceLabel;
    QLCDNumber* scoreLcd;
    QLCDNumber* levelLcd;
    QLCDNumber* linesLcd;
    QPushButton* startButton;
    QPushButton* quitButton;
    QPushButton* pauseButton;
};
