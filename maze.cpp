#include <iostream>
#include "maze.h"

Cell::Cell()
{
	l = t = r = b = true;
	v = false;
}

void Cell::Draw(double x, double y)
{
	/*if (current_view == top_view) {
		if (l)
			DrawLine(x, y, x, y + 1);
		if (b)
			DrawLine(x, y, x + 1, y);
		if (t)
			DrawLine(x, y + 1, x + 1, y + 1);
		if (r)
			DrawLine(x + 1, y, x + 1, y + 1);
	}*/
	//else {

		DrawRectangle(x, y, x + 1, y + 1);


		glColor3ub(255, 255, 255);
		DrawCube(x, y, 0, x + .1, y + .1, 1, true);
		DrawCube(x, y + .9, 0, x + .1, y + 1, 1, true);
		DrawCube(x + .9, y, 0, x + 1, y + .1, 1, true);
		DrawCube(x + .9, y + .9, 0, x + 1, y + 1, 1, true);
		if (l) {
			//glColor3ub(1352 * (int)x % 255, 646 * (int)y % 255, 1111 * (int)x % 255);
			/*glBegin(GL_QUADS);
			glVertex3d(x, y, 0);
			glVertex3d(x, y + 1, 0);
			glVertex3d(x, y + 1, 1);
			glVertex3d(x, y, 1);
			glEnd();*/
			DrawCube(x, y + .1, 0, x + .1, y + .9, 1, false);
		}
		if (r) {
			//glColor3ub(2391 * (int)x % 255, 5684 * (int)y % 255, 6464 * (int)x % 255);
			/*glBegin(GL_QUADS);
			glVertex3d(x + 1, y, 0);
			glVertex3d(x + 1, y + 1, 0);
			glVertex3d(x + 1, y + 1, 1);
			glVertex3d(x + 1, y, 1);
			glEnd();*/
			DrawCube(x + .9, y + .1, 0, x + 1, y + .9, 1, false);
		}
		if (t) {
			//glColor3ub(646 * (int)y % 255, 646 * (int)x % 255, 1120 * (int)y % 255);
			/*glBegin(GL_QUADS);
			glVertex3d(x, y + 1, 0);
			glVertex3d(x + 1, y + 1, 0);
			glVertex3d(x + 1, y + 1, 1);
			glVertex3d(x, y + 1, 1);
			glEnd();*/
			DrawCube(x + .1, y + .9, 0, x + .9, y + 1, 1, false);
		}
		if (b) {
			//glColor3ub(546 * (int)x % 255, 22 * (int)y % 255, 7578 * (int)x % 255);
			/*glBegin(GL_QUADS);
			glVertex3d(x, y, 0);
			glVertex3d(x + 1, y, 0);
			glVertex3d(x + 1, y, 1);
			glVertex3d(x, y, 1);
			glEnd();*/
			DrawCube(x + .1, y, 0, x + .9, y + .1, 1, false);
		}
	}
//}

Maze::Maze()
{
}

void Maze::Draw()
{
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			mCells[i][j].Draw(i, j);
		}
	}
}

void Maze::RemoveWalls()
{
	srand(time(0));
	mCells[0][0].b = false;
	RemoveWallsRecursive(0, 0);
	mCells[W - 1][H - 1].t = false;
}

void Maze::RemoveWallsRecursive(int i, int j)
{
	mCells[i][j].v = true;
	while (true) {
		enum NEIGHBORS { LEFT, TOP, RIGHT, BOTTOM };
		std::vector<NEIGHBORS> n;

		// Can I go left from i,j?
		if (i > 0 && !mCells[i - 1][j].v)
			n.push_back(LEFT);
			
		if (i + 1 < W && !mCells[i + 1][j].v)
			n.push_back(RIGHT);

		if (j > 0 && !mCells[i][j - 1].v)
			n.push_back(BOTTOM);

		if (j + 1 < H && !mCells[i][j + 1].v )
			n.push_back(TOP);

		if (n.size() == 0)
			return;

		// pick a random direction
		int r = rand() % n.size();
		if (n[r] == LEFT) {
			mCells[i][j].l = false;
			mCells[i - 1][j].r = false;
			RemoveWallsRecursive(i - 1, j);
		}

		else if (n[r] == RIGHT) {
			mCells[i][j].r = false;
			mCells[i + 1][j].l = false;
			RemoveWallsRecursive(i + 1, j);
		}

		else if (n[r] == TOP) {
			mCells[i][j].t = false;
			mCells[i][j + 1].b = false;
			RemoveWallsRecursive(i, j + 1);
		}

		else if (n[r] == BOTTOM) {
			mCells[i][j].b = false;
			mCells[i][j - 1].t = false;
			RemoveWallsRecursive(i, j - 1);
		}
	}
}

bool Maze::OnWall(double x1, double y1, double radius) const
{
	int cell_x = int(x1);
	int cell_y = int(y1);
	double offset_x = x1 - cell_x;
	double offset_y = y1 - cell_y;

	// does object hit left wall?
	if (mCells[cell_x][cell_y].l && offset_x - radius < 0)
		return true;
	if (mCells[cell_x][cell_y].r && offset_x + radius > 1)
		return true;
	if (mCells[cell_x][cell_y].t && offset_y + radius > 1)
		return true;
	if (mCells[cell_x][cell_y].b && offset_y - radius < 0)
		return true;

	// does object get too close to top/left corner?
	if (offset_x - radius < 0 && offset_y + radius > 1)
		return true;
	if (offset_x - radius > 1 && offset_y + radius > 1)
		return true;
	if (offset_x - radius < 0 && offset_y - radius < 0)
		return true;
	if (offset_x + radius > 1 && offset_y - radius < 0)
		return true;
	return false;
}
