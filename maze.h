#pragma once

#include <vector>
#include "glut.h"
#include "graphics.h"


const int W = 12;
const int H = 12;

class Cell {
public:
	Cell();
	void Draw(double x, double y);
	bool l, t, r, b;
	bool v;
};

class Maze {
public:
	Maze();
	void Draw();
	void RemoveWalls();
	void RemoveWallsRecursive(int i, int j);
	bool OnWall(double x1, double y1, double radius) const;
private:
	Cell mCells[W][H];
};