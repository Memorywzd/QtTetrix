#pragma once

enum TetrixShape
{
	NoShape, LineShape, SquareShape, LShape, MirroredLShape, ZShape, MirroredZShape, TShape
};

class TetrixCube
{
public:
    TetrixCube() { setShape(NoShape); }
    
	void setRandomShape();
	void setShape(TetrixShape shape);

    TetrixShape shape() const { return cubeShape; }
    int x(int index) const { return coords[index][0]; }
    int y(int index) const { return coords[index][1]; }
    int minX() const;
    int maxX() const;
    int minY() const;
    int maxY() const;
    TetrixCube rotatedLeft() const;
    TetrixCube rotatedRight() const;

private:
    void setX(int index, int x) { coords[index][0] = x; }
    void setY(int index, int y) { coords[index][1] = y; }

    TetrixShape cubeShape;
    int coords[4][2];

};

