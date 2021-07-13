#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_tetrixui.h"

class TetrixUI : public QMainWindow
{
    Q_OBJECT

public:
    TetrixUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::TetrixUIClass ui;
};
