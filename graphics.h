#pragma once

#include "keys.h"
#include "glut.h"

enum viewType {perspective_view, rat_view};
extern viewType current_view;


void DrawRectangle(double x1, double y1, double x2, double y2);
void DrawLine(double x1, double y1, double x2, double y2);
void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
void DrawCube(double x1, double y1, double z1, double x2, double y2, double z2, bool column);
float function(float x, float y);