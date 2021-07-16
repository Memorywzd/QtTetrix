#pragma once

#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include "tetrixcube.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class TetrixLogic : public QFrame
{
	Q_OBJECT

public:
	TetrixLogic(QWidget* parent = 0);

	void setNextPieceLabel(QLabel* label);
	QSize sizeHint() const override;
	QSize minimumSizeHint() const override;

public 
slots:
	void start();
	void pause();

signals:
	void scoreChanged(int score);
	void levelChanged(int level);
	void linesRemovedChanged(int numLines);

protected:
	void paintEvent(QPaintEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void timerEvent(QTimerEvent* event) override;

private:
    enum { BoardWidth = 10, BoardHeight = 22 };

    TetrixShape& shapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }
    int timeoutTime() { return 1000 / (1 + level); }
    int squareWidth() { return contentsRect().width() / BoardWidth; }
    int squareHeight() { return contentsRect().height() / BoardHeight; }
    void clearBoard();
    void dropDown();
    void oneLineDown();
    void pieceDropped(int dropHeight);
    void removeFullLines();
    void newPiece();
    void showNextPiece();
    bool tryMove(const TetrixCube& newCube, int newX, int newY);
    void drawSquare(QPainter& painter, int x, int y, TetrixShape shape);

    QBasicTimer timer;
    QPointer<QLabel> nextPieceLabel;
    bool isStarted;
    bool isPaused;
    bool isWaitingAfterLine;
    TetrixCube curCube;
    TetrixCube nextCube;
    int curX;
    int curY;
    int numLinesRemoved;
    int numPiecesDropped;
    int score;
    int level;
    TetrixShape board[BoardWidth * BoardHeight];
};
