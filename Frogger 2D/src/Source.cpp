//#include<stdio.h>
#include<stdlib.h>
#include<glut.h> 
#include<iostream>
#include <windows.h> 
#include <gl\gl.h>
#include <gl\glu.h>


void drawEnv();
void Winner();
bool collision(float , float , float, float, float, float, float, float);
void GameOver();
int flag = 1;
int lock = 0;

typedef struct cars//struct definition
{
	float xctr;
	float yctr;
} cars;

struct  cars cax[6];//instance of structure type,6 cars

GLfloat fx = 10.0, fy = 10.0;
GLfloat wx1 = 20, hy1 = 10;
GLfloat bw = 40, bh = 20;
GLfloat fw = 20, fh = 20;

typedef struct boats
{
	float xctr;
	float yctr;
} boats;

struct  boats wax[16];

int disable = 9;


void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutPostRedisplay();
	drawEnv();
	glPushMatrix();

	cax[0].xctr = 70;//stucture element ,x value
	cax[0].yctr = 190;
	cax[1].xctr = 220;
	cax[1].yctr = 190;
	cax[2].xctr = 370;
	cax[2].yctr = 190;
	cax[3].xctr = 70;
	cax[3].yctr = 75;
	cax[4].xctr = 220;
	cax[4].yctr = 75;
	cax[5].xctr = 370;
	cax[5].yctr = 75;

	wax[0].xctr = 300;
	wax[0].yctr = 320;
	wax[1].xctr = 400;
	wax[1].yctr = 320;
	wax[2].xctr = 500;
	wax[2].yctr = 320;

	wax[3].xctr = 200;
	wax[3].yctr = 360;
	wax[4].xctr = 300;
	wax[4].yctr = 360;
	wax[5].xctr = 400;
	wax[5].yctr = 360;

	wax[6].xctr = 100;
	wax[6].yctr = 400;
	wax[7].xctr = 200;
	wax[7].yctr = 400;
	wax[8].xctr = 300;
	wax[8].yctr = 400;

	wax[9].xctr = 100;
	wax[9].yctr = 440;
	wax[10].xctr = 200;
	wax[10].yctr = 440;
	wax[11].xctr = 300;
	wax[11].yctr = 440;

}

bool collision2(float x, float y, float fx, float fy)
{
	if (((fx - 2) > (x - 20)) && ((fx + 2) < (x + 20)) && ((fy + 3) < (y + 10)) && ((fy - 3) > (y - 10)))
		return true;
	return false;
}

void createboats(struct boats *bx)
{
	int x, y;
	x = bx->xctr; y = bx->yctr;
	//a = 25; b = 7; c = 7;
	glBegin(GL_QUADS);
	glColor3f(0.384, 0.164, 0.117);
	glVertex2f(x - 20, y + 10);
	glVertex2f(x - 20, y - 10);
	glVertex2f(x + 20, y - 10);
	glVertex2f(x + 20, y + 10);
	
	glEnd();
	

	if (collision2(x, y, fx, fy))
	{
		
		if (y == 320)
			fx += 0.8;
		else if (y == 360)
			fx += 1;
		else if (y == 400)
			fx += 1.3;
		else if (y == 440)
			fx += 1.1;
	}
	else
	{
		if ((flag) && fy > 300)
			if(!(fy > 450))
				GameOver();
	}

}



void createcar(struct cars *bx)
{
	int a, b, c, x, y;
	x = bx->xctr; y = bx->yctr;
	a = 20; b = 20; c = 7;
	
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x - b, y - b);
	glVertex2f(x - b, y - c);
	glVertex2f(x - c, y - c);
	glVertex2f(x, y + c);
	glVertex2f(x + c, y + c);
	glVertex2f(x + (c+5), y - c);
	glVertex2f(x + a, y - c);
	glVertex2f(x + a, y - b);
	glEnd();

	glColor3f(0, 0, 1);
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2f(x + (c - 15), y - (c + 14));
	glVertex2f(x + (b - 10), y - (c + 14));
	glEnd();

	if (collision(x, y, 20, 20, fx, fy, 5, 7))
		GameOver();

}
bool collision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	if (y1 + h1 < y2) return false;
	if (y1 > y2 + h2) return false;
	if (x1 + w1 < x2) return false;
	if (x1 > x2 + w2) return false;

	return true;
}



void drawFrog()
{
	glColor3f(0.0, 1.0, 0.0);
	// Drawing body
	glBegin(GL_POLYGON);
	glVertex2f(fx - 4, fy - 4);
	glVertex2f(fx - 2, fy - 6);
	glVertex2f(fx + 2, fy - 6);
	glVertex2f(fx + 4, fy - 4);
	glVertex2f(fx + 4, fy + 4);
	glVertex2f(fx + 2, fy + 6);
	glVertex2f(fx - 2, fy + 6);
	glVertex2f(fx - 4, fy + 4);
	glEnd();
	
	// Head
	glBegin(GL_POLYGON);
	glVertex2f(fx - 2, fy + 6);
	glVertex2f(fx + 2, fy + 6);
	glVertex2f(fx + 4, fy + 8);
	glVertex2f(fx + 4, fy + 11);
	glVertex2f(fx + 2, fy + 13);
	glVertex2f(fx    , fy + 11);
	glVertex2f(fx    , fy + 11);
	glVertex2f(fx - 2, fy + 13);
	glVertex2f(fx - 4, fy + 11);
	glVertex2f(fx - 4, fy + 8);
	glVertex2f(fx - 2, fy + 6);
	glEnd();
	// Right Hand
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(fx + 4, fy + 4);
	glVertex2f(fx + 2, fy + 6);
	glVertex2f(fx + 6, fy + 6);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(fx + 4, fy + 4);
	glVertex2f(fx + 6, fy + 6);
	glVertex2f(fx + 7, fy + 4);
	glEnd();

	// Left Hand
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(fx - 4, fy + 4);
	glVertex2f(fx - 2, fy + 6);
	glVertex2f(fx - 6, fy + 6);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(fx - 4, fy + 4);
	glVertex2f(fx - 6, fy + 6);
	glVertex2f(fx - 7, fy + 4);
	glEnd();
	// Left leg
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(fx - 4, fy - 4);
	glVertex2f(fx - 2, fy - 6);
	glVertex2f(fx - 6, fy - 6);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(fx - 6, fy - 6);
	glVertex2f(fx - 1, fy - 6);
	glVertex2f(fx - 5, fy - 8);
	glEnd();

	// Right Leg
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(fx + 4, fy - 4);
	glVertex2f(fx + 2, fy - 6);
	glVertex2f(fx + 6, fy - 6);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(fx + 6, fy - 6);
	glVertex2f(fx + 2, fy - 6);
	glVertex2f(fx + 6, fy - 8);
	glEnd();

	// Eyes
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(7);
	glBegin(GL_POINTS);
	glVertex2f(fx + 2, fy + 10);
	glVertex2f(fx - 2, fy + 10);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2f(fx + 2, fy + 11);
	glVertex2f(fx - 2, fy + 11);
	glEnd();
	
	std::cout << fx << " : " << fy << std::endl;
}

int exiter = 0;
void keys(unsigned char key, int x, int y)
{
	if (disable)
	{
		if (fy >= 280)
		{
			flag = 1;
			switch (key)
			{
			case 'w': fy = fy + 40;
				break;
			case 's': if (!lock && fy > 280)
						fy = fy - 40;
					  break;
					
			case 'a': fx = fx - 20;
				break;
			case 'd': fx = fx + 20;
				break;
			}
			
		}
	
		else
		{
			switch (key)
			{
			case 'w': fy = fy + 30;
				break;
			case 's': fy = fy - 30;
				break;
			case 'a': fx = fx - 20;
				break;
			case 'd': fx = fx + 20;
				break;
			}
		}
		
	}
	if (key == 13) 
		exiter = 1;
}


void keyBuff()
{
	bool* keyStates = new bool[256];
}
void Write(char *string) {//Write string on the screen
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}

int stop = 1;
void GameOver() {
	

	//char tmp_str[40];
	disable = 0;
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRasterPos2f(200, 252);
	Write((char *)(" ********GAME OVER********"));
	glColor3f(1, 0, 0);
	glRasterPos2f(230, 225);
	Write((char *)("Press Enter to Exit"));
	stop = 0;
	if(exiter)
		exit(0);
	glPopMatrix();

}
void Winner() {
	//char tmp_str[40];
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRasterPos2f(200, 252);
	Write((char *)(" ********WINNER********"));
	glColor3f(1, 0, 0);
	glRasterPos2f(222, 225);
	Write((char *)("Press Enter to Exit"));
	stop = 0;
	if (exiter)
		exit(0);
}
void line() {
	glPushMatrix();
	glColor3f(1, 1, 1);
	glRasterPos2f(220, 5);
	Write((char *)(" START "));
	glColor3f(1, 1, 1);
	glRasterPos2f(220, 475);
	Write((char *)(" FINISH "));
	glPopMatrix();
}

void drawEnv()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 250.0);
	glVertex2f(500.0, 250.0);
	glVertex2f(500.0, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(0.0, 250.0);
	glVertex2f(0.0, 265.0);
	glVertex2f(500.0, 265.0);
	glVertex2f(500.0, 250.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.0, 280.0);
	glVertex2f(0.0, 500.0);
	glVertex2f(500.0, 500.0);
	glVertex2f(500.0, 280.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 30.0);
	glVertex2f(500.0, 30.0);
	glVertex2f(500.0, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(500.0, 500.0);
	glVertex2f(0.0, 500.0);
	glVertex2f(0.0, 470.0);
	glVertex2f(500.0, 470.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(50.0, 120.0);
	glVertex2f(50.0, 130.0);
	glVertex2f(120.0, 130.0);
	glVertex2f(120.0, 120.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(180.0, 120.0);
	glVertex2f(180.0, 130.0);
	glVertex2f(250.0, 130.0);
	glVertex2f(250.0, 120.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(310.0, 120.0);
	glVertex2f(310.0, 130.0);
	glVertex2f(380.0, 130.0);
	glVertex2f(380.0, 120.0);
	glEnd();



}

void display()
{

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	drawEnv();

	createcar(&cax[0]);
	createcar(&cax[1]);
	createcar(&cax[2]);
	createcar(&cax[3]);
	createcar(&cax[4]);
	createcar(&cax[5]);

	
	if (stop)
	{

		if (cax[0].xctr < 600)
			cax[0].xctr = cax[0].xctr + 1;
		else
			cax[0].xctr = 0;

		if (cax[1].xctr < 600)
			cax[1].xctr = cax[1].xctr + 1;
		else
			cax[1].xctr
			= 0;

		if (cax[2].xctr < 600)
			cax[2].xctr = cax[2].xctr + 1;
		else
			cax[2].xctr
			= 0;


		if (cax[3].xctr < -100)
			cax[3].xctr
			= 500;

		else
			cax[3].xctr = cax[3].xctr - 1;

		if (cax[4].xctr < -100)
			cax[4].xctr
			= 500;

		else
			cax[4].xctr = cax[4].xctr - 1;

		if (cax[5].xctr < -100)
			cax[5].xctr
			= 500;

		else
			cax[5].xctr = cax[5].xctr - 1;

	}
	
	for (int i = 0; i < 12; i++)
	{
		if (collision2(wax[i].xctr, wax[i].yctr, fx, fy))
			flag = 0;
	}

	createboats(&wax[0]);
	createboats(&wax[1]);
	createboats(&wax[2]);
	createboats(&wax[3]);
	createboats(&wax[4]);
	createboats(&wax[5]);
	createboats(&wax[6]);
	createboats(&wax[7]);
	createboats(&wax[8]);
	createboats(&wax[9]);
	createboats(&wax[10]);
	createboats(&wax[11]);
	
	
	if (fy > 450)
		Winner();
	
	if (stop)
	{


		if (wax[0].xctr < 600)
			wax[0].xctr = wax[0].xctr + 0.8;
		else
			wax[0].xctr = 0;

		if (wax[1].xctr < 600)
			wax[1].xctr = wax[1].xctr + 0.8;
		else
			wax[1].xctr = 0;
		if (wax[2].xctr < 600)
			wax[2].xctr = wax[2].xctr + 0.8;
		else
			wax[2].xctr = 0;
		
		if (wax[3].xctr < 600)
			wax[3].xctr += 1;
		else
			wax[3].xctr = -10;

		if (wax[4].xctr < 600)
			wax[4].xctr += 1;
		else
			wax[4].xctr = -10;

		if (wax[5].xctr < 600)
			wax[5].xctr += 1;
		else
			wax[5].xctr = -10;

		if (wax[6].xctr < 600)
			wax[6].xctr = wax[6].xctr + 1.3;
		else
			wax[6].xctr = 0;

		if (wax[7].xctr < 600)
			wax[7].xctr = wax[7].xctr + 1.3;
		else
			wax[7].xctr = 0;
		if (wax[8].xctr < 600)
			wax[8].xctr = wax[8].xctr + 1.3;
		else
			wax[8].xctr= 0;

		if (wax[9].xctr < 600)
			wax[9].xctr += 1.1;
		else
			wax[9].xctr = 0;

		if (wax[10].xctr < 600)
			wax[10].xctr += 1.1;
		else
			wax[10].xctr = 0;

		if (wax[11].xctr < 600)
			wax[11].xctr += 1.1;
		else	
			wax[11].xctr = 0;
	}
	
	if (fx > 300)
		lock = 1;

	drawFrog();
	line();


	glutPostRedisplay();

	glutSwapBuffers();
	glFlush();

}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("frogger");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keys);
	init();

	glutMainLoop();
	return 0;

}


