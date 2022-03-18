#include <ctime>
#include "rat.h"

double GetDeltaTime()
{
	static clock_t start_time = clock();
	static int current_frame = 0;
	clock_t current_time = clock();
	current_frame += 1;
	double total_time = (double(current_time) - double(start_time)) / CLOCKS_PER_SEC;
	if (total_time == 0)
		total_time = .00001;
	double frames_per_second = (double)current_frame / total_time;
	double DT = 1.0 / frames_per_second;
	return DT;
}

Rat::Rat()
{
	x = 50;
	y = 50;
	degrees = 0;
	speed = 2;
	radius = .15;
	flyingHeight = 1.0;
	waterHeight = -2.0;
}

Rat::Rat(double x, double y)
	: x(x), y(y) {
	degrees = 0;
	speed = 1;
	radius = .15;
	flyingHeight = 1.0;
	waterHeight = -2.0;
}

void Rat::Draw()
{
	if (current_view == rat_view)
		return;
	glPushMatrix();
	glTranslated(x, y, 0);
	glRotated(degrees, 0, 0, 1);
	glScaled(.5, .5, 1.0);
	glColor3ub(155, 150, 155);
	
	// Bottom
	DrawTriangle(.6, 0, -.4, .2, -.4, -.2);
	
	glBegin(GL_TRIANGLES);
	// Left upper
	glVertex3d(.6, 0, 0);
	glVertex3d(-.4, .2, 0);
	glVertex3d(-.3, 0, .2);

	// Right upper
	glVertex3d(.6, 0, 0);
	glVertex3d(-.4, -.2, 0);
	glVertex3d(-.3, 0, .2);

	// Back
	glVertex3d(-.4, .2, 0);
	glVertex3d(-.4, -.2, 0);
	glVertex3d(-.3, 0, .2);
	glEnd();

	glPopMatrix();
}

void Rat::Update(const Maze& m)
{
}

void Rat::MoveBackward()
{
	this->x -= this->GetDX() * speed;
	this->y -= this->GetDY() * speed;
}

void Rat::RotateRight(double DT)
{
	degrees -= 120 * DT;
}

void Rat::RotateLeft(double DT)
{
	degrees += 120 * DT;
}

double Rat::GetDX()
{
	double rads = this->degrees * 3.1415926 / 180;
	double dx = std::cos(rads);
	return dx;
}

double Rat::GetDY()
{
	double rads = this->degrees * 3.1415926 / 180;
	double dy = std::sin(rads);
	return dy;
}

float Rat::GetDXUnscaled()
{
	return GetDX();
}

float Rat::GetDYUnscaled()
{
	return GetDY();
}

double Rat::GetX()
{
	return x;
}

double Rat::GetY()
{
	return y;
}

double Rat::GetZ(float xpos, float ypos)
{
	float terrainHeight = function(xpos, ypos);
	if (terrainHeight < waterHeight)
	{
		terrainHeight = waterHeight;
	}
	float z = terrainHeight + flyingHeight;
	return z;
}

double Rat::GetRadius()
{
	return radius;
}

double Rat::GetNextX(double DT)
{
	return x + GetDX() * speed * DT;
}

double Rat::GetNextY(double DT)
{
	return y + GetDY() * speed * DT;
}

double Rat::GetWaterHeight()
{
	return waterHeight;
}

void Rat::SetY(double newy)
{
	y = newy;
}

void Rat::SetWaterHeight(double w)
{
	waterHeight = w;
}

void Rat::SetX(double newx)
{
	x = newx;
}

void Rat::MoveForward(const Maze& m, double DT)
{
	/*if (!m.OnWall(GetNextX(DT), GetNextY(DT), GetRadius())) {
		this->x += this->GetDX() * speed * DT;
		this->y += this->GetDY() * speed * DT;
	}
	else if (!m.OnWall(GetNextX(DT), GetY(), GetRadius()))
		SetX(GetNextX(DT));
	else if (!m.OnWall(GetX(), GetNextY(DT), GetRadius()))
		SetY(GetNextY(DT));*/
	this->x += this->GetDX() * speed * DT;
	this->y += this->GetDY() * speed * DT;
}
