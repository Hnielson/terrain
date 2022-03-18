#pragma once
#include <cmath>
#include "maze.h"
#include "graphics.h"

double GetDeltaTime();

class Rat {
private:
	double x, y, degrees, speed, radius, waterHeight, flyingHeight;
public:
	Rat();
	Rat(double x, double y);
	void Draw();
	void Update(const Maze& m);
	void MoveForward(const Maze& m, double DT);
	void MoveBackward();
	void RotateRight(double DT);
	void RotateLeft(double DT);
	

	double GetDX();
	double GetDY();
	float GetDXUnscaled();
	float GetDYUnscaled();
	double GetX();
	double GetY();
	double GetZ(float xpos, float ypos);
	double GetRadius();
	double GetNextX(double DT);
	double GetNextY(double DT);
	double GetWaterHeight();
	void SetX(double newx);
	void SetY(double newy);
	void SetWaterHeight(double w);
};