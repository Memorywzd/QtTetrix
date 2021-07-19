#include <QtCore>
#include <QDebug>
#include "tetrixcube.h"


void TetrixCube::setRandShape() 
{
    int randShape = QRandomGenerator::global()->bounded(7) + 1;
    setShape(TetrixShape(randShape));
}

void TetrixCube::setShape(TetrixShape shape)
{
    static const int coordsTable[8][4][2] =
    {
        { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
        { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
        { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
        { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } },
        { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
        { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
        { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } }
    };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; ++j)
            key_points[i][j] = coordsTable[shape][i][j];
    }
    cubeShape = shape;
}

int TetrixCube::minX() const
{
    int min = key_points[0][0];
    for (int i = 1; i < 4; ++i)
        min = qMin(min, key_points[i][0]);
    return min;
}
int TetrixCube::maxX() const
{
    int max = key_points[0][0];
    for (int i = 1; i < 4; ++i)
        max = qMax(max, key_points[i][0]);
    return max;
}

int TetrixCube::minY() const
{
    int min = key_points[0][1];
    for (int i = 1; i < 4; ++i)
        min = qMin(min, key_points[i][1]);
    return min;
}

int TetrixCube::maxY() const
{
    int max = key_points[0][1];
    for (int i = 1; i < 4; ++i)
        max = qMax(max, key_points[i][1]);
    return max;
}

TetrixCube TetrixCube::rotateLeft() const
{
    if (cubeShape == SquareShape)
        return *this;

    TetrixCube t;
    t.cubeShape = cubeShape;
    for (int i = 0; i < 4; ++i)
    {
        t.setX(i, key_point_y(i));
        t.setY(i, -key_point_x(i));
    }
    return t;
}

TetrixCube TetrixCube::rotateRight() const
{
    if (cubeShape == SquareShape)
        return *this;

    TetrixCube t;
    t.cubeShape = cubeShape;
    for (int i = 0; i < 4; ++i)
    {
        t.setX(i, -key_point_y(i));
        t.setY(i, key_point_x(i));
    }
    return t;
}
