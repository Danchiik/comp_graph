#pragma once
#include "stdio.h"
#include "math.h"
#define X 0
#define Y 1
#define Z 2
#define W 3
#define M_PI 3.1415

class point
{
	float* mul(float mtx[4][4])
	{
		float x_ = x;
		float y_ = y;
		float z_ = z;
		float w_ = w;
		float temp[4] = { x, y, z, w };
		float res[4] = { 0,0,0,0 };

		res[X] = temp[0] * mtx[0][0] + temp[1] * mtx[1][0] + temp[2] * mtx[2][0] + temp[3] * mtx[3][0];
		res[Y] = temp[0] * mtx[0][1] + temp[1] * mtx[1][1] + temp[2] * mtx[2][1] + temp[3] * mtx[3][1];
		res[Z] = temp[0] * mtx[0][2] + temp[1] * mtx[1][2] + temp[2] * mtx[2][2] + temp[3] * mtx[3][2];
		res[W] = temp[0] * mtx[0][3] + temp[1] * mtx[1][3] + temp[2] * mtx[2][3] + temp[3] * mtx[3][3];

		x = res[X];
		y = res[Y];
		z = res[Z];
		w = res[W];
		return res;
	}


public:

	float x, y, z, w;
	point(int _x, int _y, int _z) : x(_x), y(_y), z(_z)
	{
		w = 1;
	}
	point()
	{
		x = 0; y = 0; z = 0; w = 1;
	}


	void move(float _x, float _y, float _z)
	{
		float matrix[4][4] = {
			1,  0,  0,  0,	0,  1,  0,  0,
			0,  0,  1,  0,	_x, _y, _z, 1 };

		mul(matrix);
	}

	void scale(float _x, float _y, float _z) {
		float matrix[4][4] = {
			_x, 0, 0, 0, 0, _y, 0, 0,
			0, 0, _z, 0, 0, 0, 0, 1 };

		mul(matrix);
	}


	void rotateX(float phi) {
		phi *= M_PI / 180;

		float matrix[4][4] = {
			1, 0, 0, 0,	0, cos(phi), -sin(phi), 0,
			0, sin(phi), cos(phi), 0, 0, 0, 0, 1 };
		mul(matrix);
	}

	void rotateY(float phi) {
		phi *= M_PI / 180;

		float matrix[4][4] = {
			cos(phi), 0, -sin(phi), 0,0, 1, 0, 0,
			sin(phi), 0, cos(phi), 0,	0, 0, 0, 1 };
		mul(matrix);
	}

	void rotateZ(float phi) {
		phi *= M_PI / 180;

		float matrix[4][4] = {
			cos(phi), -sin(phi), 0, 0,	sin(phi), cos(phi), 0, 0,
			0, 0, 1, 0,		0, 0, 0, 1 };
		mul(matrix);
	}

};
class plane
{

public:
	point** v;
	int point_number;
	int color;
	float A, B, C, D;

	point* middle;

	void upd_middle()
	{
		middle->x = 0;
		middle->y = 0;
		middle->z = 0;
		for (int i = 0; i < point_number; i++)
		{
			middle->x += v[i]->x;
			middle->y += v[i]->y;
			middle->z += v[i]->z;
		}
		middle->x /= point_number;
		middle->y /= point_number;
		middle->z /= point_number;

	}


	plane(point* _A, point* _B, point* _C, int c)
	{
		point_number = 3;
		v = new point * [point_number];
		v[0] = _A;
		v[1] = _B;
		v[2] = _C;

		color = c;
		middle = new point();
		upd();
	}

	plane(point* _A, point* _B, point* _C, point* _D, int c)
	{
		point_number = 4;
		v = new point * [point_number];
		v[0] = _A;
		v[1] = _B;
		v[2] = _C;
		v[3] = _D;
		middle = new point();
		color = c;
		upd();
	}



	void upd()
	{
		int i = 1;
		float M[3] = { v[i]->x, v[i]->y, v[i]->z };
		int ai = i - 1;		
		int bi = i + 1;
		float a[3] = { v[ai]->x - v[i]->x, v[ai]->y - v[i]->y, v[ai]->z - v[i]->z };
		float b[3] = { v[bi]->x - v[i]->x, v[bi]->y - v[i]->y, v[bi]->z - v[i]->z };
		A = a[Y] * b[Z] - a[Z] * b[Y];
		B -= a[X] * b[Z] - a[Z] * b[X];B = -B;		
		C = a[X] * b[Y] - a[Y] * b[X];
		D = M[X] * A + M[Y] * B + M[Z] * C;D = -D;		
	}
};