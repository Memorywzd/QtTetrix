#include <QtCore>
#include <iostream>
#include "tetrixcube.h"


void TetrixCube::setRandomShape()
{
    setShape(TetrixShape(QRandomGenerator::global()->bounded(7) + 1));
}

void TetrixCube::setShape(TetrixShape shape)
{
    static const int coordsTable[8][4][2] =
    {
        { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
        { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
        { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
        { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } },
        { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
        { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
        { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } }
    };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; ++j)
            coords[i][j] = coordsTable[shape][i][j];
    }
    cubeShape = shape;
}

int TetrixCube::minX() const
{
    int min = coords[0][0];
    for (int i = 1; i < 4; ++i)
        min = qMin(min, coords[i][0]);
    return min;
}
int TetrixCube::maxX() const
{
    int max = coords[0][0];
    for (int i = 1; i < 4; ++i)
        max = qMax(max, coords[i][0]);
    return max;
}

int TetrixCube::minY() const
{
    int min = coords[0][1];
    for (int i = 1; i < 4; ++i)
        min = qMin(min, coords[i][1]);
    return min;
}

int TetrixCube::maxY() const
{
    int max = coords[0][1];
    for (int i = 1; i < 4; ++i)
        max = qMax(max, coords[i][1]);
    return max;
}

TetrixCube TetrixCube::rotatedLeft() const
{
    if (cubeShape == SquareShape)
        return *this;

    TetrixCube result;
    result.cubeShape = cubeShape;
    for (int i = 0; i < 4; ++i)
    {
        result.setX(i, y(i));
        result.setY(i, -x(i));
    }
    return result;
}

TetrixCube TetrixCube::rotatedRight() const
{
    if (cubeShape == SquareShape)
        return *this;

    TetrixCube result;
    result.cubeShape = cubeShape;
    for (int i = 0; i < 4; ++i) {
        result.setX(i, -y(i));
        result.setY(i, x(i));
    }
    return result;
}
