#include <QDebug>
#include <QtWidgets>

#include "tetrixlogic.h"

TetrixLogic::TetrixLogic(QWidget *parent)
	: QFrame(parent)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    isStarted = false;
    isPaused = false;
    initArea(); qDebug() << "TetrixLogic(): init the area." << endl;
    cubeNow.setShape(NoShape); 
    qDebug() << "TetrixLogic(): set current shape to NoShape." << endl;
    
    cubeNext.setRandShape();
    qDebug() << "TetrixLogic(): set next shape to randShape()." << endl;
}

void TetrixLogic::createCube()
{
    cubeNow = cubeNext;
    cubeNext.setRandShape();
    promptNextCube();
    cubeX = blockNumW / 2;
    cubeY = blockNumH - 1 + cubeNow.minY();
    promptBottom();

    if (!move(cubeNow, cubeX, cubeY))
    {
        cubeNow.setShape(NoShape);
        game_timer.stop();
        isStarted = false;
    }
}

bool TetrixLogic::move(const TetrixCube& newCube, int newX, int newY)
{
    for (int i = 0; i < 4; ++i)
    {
        int x = newX + newCube.key_point_x(i);
        int y = newY - newCube.key_point_y(i);
        if (x < 0 || x >= blockNumW || y < 0 || y >= blockNumH)
            return false;
        if (blocks_shape[(y * blockNumW) + x] != NoShape)
            return false;
    }
    cubeNow = newCube;
    cubeX = newX;
    cubeY = newY;
    //update();
    return true;
}

bool TetrixLogic::proMove(const TetrixCube& newCube, int newX, int newY)
{
    for (int i = 0; i < 4; ++i)
    {
        int x = newX + newCube.key_point_x(i);
        int y = newY - newCube.key_point_y(i);
        if (x < 0 || x >= blockNumW || y < 0 || y >= blockNumH)
            return false;
        if (blocks_shape[(y * blockNumW) + x] != NoShape)
            return false;
    }
    cubeBottom = newCube;
    bottomX = newX;
    bottomY = newY;
    update();
    return true;
}

void TetrixLogic::initArea()
{
    for (int i = 0; i < blockNumH * blockNumW; ++i)
        blocks_shape[i] = NoShape;
}

void TetrixLogic::start()
{
    isStarted = true;
    removedLines = 0;
    score = 0;
    level = 1;
    initArea();

    emit scoreChanged(score);
    emit levelChanged(level);
    emit removedLinesChanged(removedLines);

    createCube();
    game_timer.start(refresh_time, this);
}

void TetrixLogic::pause()
{
    qDebug() << "pause(): pause event activated!" << endl;
//    isPaused = true;
//    game_timer.stop();
}

void TetrixLogic::cubeFall()
{
    for (int i = 0; i < 4; ++i)
    {
        int x = cubeX + cubeNow.key_point_x(i);
        int y = cubeY - cubeNow.key_point_y(i);
        blocks_shape[(y * blockNumW) + x] = cubeNow.shape();
    }
    bool flag1 = move(cubeNow, cubeX, cubeY - 1);
    if (!flag1)
    {
        removeFullLines();
        createCube();
    }
        
}

void TetrixLogic::removeFullLines()
{
    int numFullLines = 0;
    for (int i = blockNumH - 1; i >= 0; i--)
    {
        bool lineIsFull = true;
        for (int j = 0; j < blockNumW; j++)
        {
            if (blocks_shape[(i * blockNumW) + j] == NoShape)
            {
                lineIsFull = false;
                break;
            }
        }
        if (lineIsFull)
        {
            ++numFullLines;
            for (int k = i; k < blockNumH - 1; k++)
            {
                for (int j = 0; j < blockNumW; j++)
                    blocks_shape[(k * blockNumW) + j] = blocks_shape[((k + 1) * blockNumW) + j];
            }
           
        }
    }
    if (numFullLines > 0)
    {
        removedLines += numFullLines;
        if (numFullLines == 1)
        {
            score++;
        }
        else
        {
            score += numFullLines * numFullLines;
        }
        emit removedLinesChanged(removedLines);
        emit scoreChanged(score);
        update();
    }
}

void TetrixLogic::toBottom()
{
    int newY = cubeY;
    while (newY > 0)
    {
        if (!move(cubeNow, cubeX, newY - 1))break;
        newY--;
    }
    cubeFall();
}

void TetrixLogic::promptNextCube()
{
    if (!nextCubeLabel)return;

    int dx = cubeNext.maxX() - cubeNext.minX() + 1;
    int dy = cubeNext.maxY() - cubeNext.minY() + 1;

    QPixmap pixmap(dx * blockUnitWidth(), dy * blockUnitHeight());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), nextCubeLabel->palette().background());

    for (int i = 0; i < 4; ++i)
    {
        int x = cubeNext.key_point_x(i) - cubeNext.minX();
        int y = cubeNext.key_point_y(i) - cubeNext.minY();
        painteBlock(painter, x * blockUnitWidth(), y * blockUnitHeight(), cubeNext.shape());
    }
    nextCubeLabel->setPixmap(pixmap);
}

void TetrixLogic::promptBottom()
{
    cubeBottom = cubeNow;
    bottomX = cubeX;
    bottomY = cubeY;
    int newY = bottomY;
    while (newY > 0)
    {
        if (!proMove(cubeBottom, bottomX, newY - 1))break;
        newY--;
    }
    update();
}

void TetrixLogic::painteBlock(QPainter& painter, int x, int y, TetrixShape shape, int flag)
{
    static const QRgb colorTable[8] =
    {
        0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
        0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
    };
    QColor color;
    if (flag)
    {
        color = colorTable[shape];
    }
    else
    {
        color = 0xCCCCCC;
    }
    
    painter.fillRect(x + 1, y + 1, blockUnitWidth() - 2, blockUnitHeight() - 2,color);

    painter.setPen(color.light());
    painter.drawLine(x, y + blockUnitHeight() - 1, x, y);
    painter.drawLine(x, y, x + blockUnitWidth() - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + blockUnitHeight() - 1,x + blockUnitWidth() - 1, y + blockUnitHeight() - 1);
    painter.drawLine(x + blockUnitWidth() - 1, y + blockUnitHeight() - 1,x + blockUnitWidth() - 1, y + 1);
}

void TetrixLogic::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);
    QRect rect = contentsRect();
    int boardTop = rect.bottom() - blockNumH * blockUnitHeight();

    for (int i = 0; i < blockNumH; ++i)
    {
        for (int j = 0; j < blockNumW; ++j)
        {
            TetrixShape shape = blocks_shape[((blockNumH - i - 1) * blockNumW) + j];
            if (shape != NoShape)
                painteBlock(painter, rect.left() + j * blockUnitWidth(),
                    boardTop + i * blockUnitHeight(), shape);
        }
    }
    if (cubeBottom.shape() != NoShape)
    {
        for (int i = 0; i < 4; ++i)
        {
            int x = bottomX + cubeBottom.key_point_x(i);
            int y = bottomY - cubeBottom.key_point_y(i);
            painteBlock(painter, rect.left() + x * blockUnitWidth(),
                boardTop + (blockNumH - y - 1) * blockUnitHeight(),
                cubeBottom.shape(), 0);
        }
    }
    qDebug() << "paintEvent(): bottomX is: " << bottomX << ".";
    qDebug() << "paintEvent(): bottomY is: " << bottomY << ".";
    if (cubeNow.shape() != NoShape)
    {
        for (int i = 0; i < 4; ++i)
        {
            int x = cubeX + cubeNow.key_point_x(i);
            int y = cubeY - cubeNow.key_point_y(i);
            painteBlock(painter, rect.left() + x * blockUnitWidth(),
                boardTop + (blockNumH - y - 1) * blockUnitHeight(),
                cubeNow.shape());
        }
    }
    qDebug() << "paintEvent(): cubeX is: " << cubeX << ".";
    qDebug() << "paintEvent(): cubeY is: " << cubeY << ".";
}

void TetrixLogic::keyPressEvent(QKeyEvent* event)
{
    if (!isStarted || isPaused || cubeNow.shape() == NoShape)
    {
        QFrame::keyPressEvent(event);
        return;
    }
    switch (event->key())
    {
    case Qt::Key_Left:
        move(cubeNow, cubeX - 1, cubeY);
        promptBottom();
        break;
    case Qt::Key_Right:
        move(cubeNow, cubeX + 1, cubeY);
        promptBottom();
        break;
    case Qt::Key_Down:
        move(cubeNow.rotateRight(), cubeX, cubeY);
        promptBottom();
        break;
    case Qt::Key_Up:
        move(cubeNow.rotateLeft(), cubeX, cubeY);
        promptBottom();
        break;
    case Qt::Key_Space:
        toBottom();
        break;
    case Qt::Key_D:
        move(cubeNow, cubeX, cubeY - 1);
        promptBottom();
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}

void TetrixLogic::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == game_timer.timerId())
    {
        if (!move(cubeNow, cubeX, cubeY - 1))
            cubeFall();
        update();
        qDebug() << "timerEvent(): move.";
    }
    else
    {
        QFrame::timerEvent(event);
    }
}
