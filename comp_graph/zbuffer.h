#pragma once
#include "../libwinbgi/src/graphics.h"
#include <stdio.h>
#include "grafica.h"
#include "prism.h"

#include <stdio.h>
#include <queue>
#include <iostream>

#define DEPTH 0
#define COLOR 1
#define FRAME_SIZE 500

using namespace std;

class zbuffer
{

	float arr[FRAME_SIZE][FRAME_SIZE][2] = { 0 };
	point* p1 = new point;
	point* p2 = new point;
	point* p0 = new point;

	vector<pair<int, int>> stack;

	void clean()
	{
		for (int i = 0; i < FRAME_SIZE; i++)
			for (int j = 0; j < FRAME_SIZE; j++)
			{
				arr[i][j][DEPTH] = -100000;
				arr[i][j][COLOR] = 0;
			}
	
	}

	void is_visible(point* p, point* p1, point* p2, bool* pointSeen)
	{
		*pointSeen = ((p->x - p1->x) * (p2->y - p1->y) - (p->y - p1->y) * (p2->x - p1->x) >= 0);
	}


	bool is_inside(plane* p, float x, float y)
	{
		bool flag = false;
		int j = 0;
		p0->x = x;
		p0->y = y;

		for (int i = 0; i < p->point_number; i++)
		{
			j = i + 1;
			if (i == p->point_number - 1)
				j = 0;

			p1->x = p->v[j]->x;
			p1->y = p->v[j]->y;
			p2->x = p->v[i]->x;
			p2->y = p->v[i]->y;

			is_visible(p0, p1, p2, &flag);

			if (!flag)	return (false);

		}
		return (flag);
	}

	void getZ(plane* p, int x, int y, int* z)
	{
		if (p->C == 0)
			for (int i = 1; i < p->point_number; i++)
			*z = max(p->v[i]->z, p->v[i - 1]->z);
		else
			*z = -(p->A * x + p->B * y + p->D) / p->C;
	}


	

	void stack_plane(plane* p, int x, int y)
	{
		if (!is_inside(p, x, y) || x < 0 || y < 0 || x >= FRAME_SIZE || y >= FRAME_SIZE)
			return;

		stack.push_back(make_pair(x, y));

		if (!(find(stack.begin(), stack.end(), make_pair(x + 1, y)) != stack.end()))
			stack_plane(p, x + 1, y);

		if (!(find(stack.begin(), stack.end(), make_pair(x, y + 1)) != stack.end()))
			stack_plane(p, x, y + 1);

		if (!(find(stack.begin(), stack.end(), make_pair(x - 1, y)) != stack.end()))
			stack_plane(p, x - 1, y);

		if (!(find(stack.begin(), stack.end(), make_pair(x, y - 1)) != stack.end()))
			stack_plane(p, x, y - 1);
	}

	void upd_depth(plane* p, int fill_color)
	{
		std::pair<int, int > ptr;
		int z;

		while (stack.size() != 0)
		{
			ptr = stack.back();
			stack.pop_back();
			int x = ptr.first;
			int y = ptr.second;
			getZ(p, x, y, &z);

			if (z > arr[x][y][DEPTH])
			{
				arr[x][y][DEPTH] = z;
				arr[x][y][COLOR] = fill_color;
			}
		}
	}


public:

	void update_data(Prisma** p, int n)
	{
		clean();

		for (int i = 0; i < n; i++)
		{
			p[i]->proj();
			p[i]->upd_middle();
			p[i]->create_shadow();

			for (int j = 0; j < p[i]->side_num; j++)
			{
				p[i]->sides[j]->upd();
				p[i]->sides[j]->upd_middle();
				
				stack_plane(p[i]->sides[j], p[i]->sides[j]->middle->x, p[i]->sides[j]->middle->y);
				upd_depth(p[i]->sides[j], p[i]->sides[j]->color);
			}

			p[i]->unproj();
		}
		
	}


	void output_to_screen()
	{
		for (int i = 0; i < FRAME_SIZE; i++)
			for (int j = 0; j < FRAME_SIZE; j++)
				putpixel(i, j, arr[i][j][COLOR]);

	}

};