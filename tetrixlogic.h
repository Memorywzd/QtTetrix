#pragma once

#include <QBasicTimer>
#include <QFrame>
#include "tetrixcube.h"

const int blockNumH = 20;
const int blockNumW = 10;

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class TetrixLogic : public QFrame
{
    Q_OBJECT

public:
    TetrixLogic(QWidget* parent = 0);
    //QBasicTimer run_timer;
    void setNextCubeLabel(QLabel* label)
    {
        nextCubeLabel = label;
    }

public slots:
    void start();
    void pause();

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void removedLinesChanged(int lines);

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void timerEvent(QTimerEvent* event) override;

private:
    void createCube();
    bool move(const TetrixCube&, int, int);
    void initArea();
    void cubeFall(int flag = 0);
    void removeFullLines();
    void toBottom();
    void painteBlock(QPainter&, int, int, TetrixShape, int flag = 1);
    void promptNextCube();
    void promptBottom();
    bool proMove(const TetrixCube&, int, int);
    
    int blockUnitWidth()
    {
        return contentsRect().width() / blockNumW;
    }
    int blockUnitHeight()
    {
        return contentsRect().height() / blockNumH;
    }
    
    bool isStarted;
    bool isPaused;
    int removedLines;
    int score;
    int level;
    int refresh_time = 1000;
    int cubeX;
    int cubeY;
    int bottomX;
    int bottomY;
    QBasicTimer game_timer;
    TetrixCube cubeNow;
    TetrixCube cubeNext;
    TetrixCube cubeBottom;
    TetrixShape blocks_shape[blockNumH * blockNumW];
    QLabel* nextCubeLabel;
};
//游戏区域定义为Area，其中包括若干不同shape的cube
//每个cube有4个block
//每个block均含有一对坐标存储于key_points[2]数组
