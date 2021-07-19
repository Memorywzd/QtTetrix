#pragma once


enum TetrixShape
{
	NoShape, LineShape, SquareShape, LShape, MirroredLShape, ZShape, MirroredZShape, TShape
};


class TetrixCube
{
public:
    TetrixCube() { setShape(NoShape); }                    
    
	void setRandShape();                                 
	void setShape(TetrixShape shape);                      

    TetrixShape shape() const { return cubeShape; }        
    int key_point_x(int index) const { return key_points[index][0]; }
    int key_point_y(int index) const { return key_points[index][1]; }
    int minX() const;
    int maxX() const;
    int minY() const;
    int maxY() const;
    TetrixCube rotateLeft() const;
    TetrixCube rotateRight() const;

private:
    TetrixShape cubeShape;
    int key_points[4][2];

    void setX(int index, int x) { key_points[index][0] = x; }
    void setY(int index, int key_point_y) { key_points[index][1] = key_point_y; }
};

