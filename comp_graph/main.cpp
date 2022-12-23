#include "../libwinbgi/src/graphics.h"
#include <stdio.h>
#include "zbuffer.h"
#include "prism.h"


int main()
{
	
	Prisma* p1 = new Prisma();		
	p1->move(100, 210, 0);
	
	Prisma* p2 = new Prisma();	
	p2->move(300, 240, 10);
	p2->rotateY(60);
	p2->rotateX(-50);

	zbuffer buf;
	Prisma* figures[2] = { p1, p2};
	
	initwindow(FRAME_SIZE, FRAME_SIZE);
	char c;
	while (true)
	{
		
		buf.update_data(figures, 2);
		buf.output_to_screen();
		
		c = getch();
		
		switch (c)
		{
		case '0':	closegraph();	return 0;

		case 'w':p1->move(0, -30, 0);break;
		case 's':p1->move(0, 30, 0);break;
		case 'q':p1->move(0, 0, 30);break;
		case 'e':p1->move(0, 0, -30);break;
		case 'r':p1->rotateX(35);break;
		case 't':p1->rotateX(-35);break;
		case 'f':p1->rotateY(35);break;
		case 'g':p1->rotateY(-35);break;
		case 'v':p1->rotateZ(35);break;
		case 'b':p1->rotateZ(-35);break;
		case 'z':p1->scale(2, 2, 2);break;
		case 'x':p1->scale(0.5, 0.5, 0.5);break;

		case 'd':p1->move(30, 0, 0);break;
		case 'a':p1->move(-30, 0, 0);break;
		case 'k':p2->move(30, 0, 0);break;
		case 'h':p2->move(-30, 0, 0);break;
		case 'u':p2->move(0, -30, 0);break;
		case 'j':p2->move(0, 30, 0);break;
		case 'y':p2->move(0, 0, 30);break;
		case 'i':p2->move(0, 0, -30);break;
		case 'o':p2->rotateX(35);break;
		case 'p':p2->rotateX(-35);break;
		case 'l':p2->rotateY(35);break;
		case ';':p2->rotateY(-35);break;
		case ',':p2->rotateZ(35);break;
		case '.':p2->rotateZ(-35);break;
		case 'n':p2->scale(2, 2, 2);break;
		case 'm':p2->scale(0.5, 0.5, 0.5);break;
		
		default:printf("\tunknown\n");	break;
		}
	}
	closegraph();


}