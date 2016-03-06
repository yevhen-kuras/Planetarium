#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h> 
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\freeglut\glut.h"
#include "RenderModel.h"
#include "util.h"
#include "Planet.h"
int year = 0, day = 0;
Color c;
void init();
void display(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void timer_func(int n);
void planet(float radius, float dist, float rotate, Color solidColor )
{
	glColor3b((GLbyte)solidColor.R, (GLbyte)solidColor.G, (GLbyte)solidColor.B);
	glTranslatef(dist, 0.0, 0.0);
	glRotatef(rotate, 0.0, 1.0, 0.0);
	glutSolidSphere(radius, 10, 8);
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("PlanetarySystem");
	RenderModel *rm = new RenderModel();
	RenderModel::CurrentModel = rm;
	rm->init();
	//init();
	/*glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	timer_func(50);*/
	glutMainLoop();
	delete rm;
	return 0;
}
void timer_func(int n)
{
	keyboard('d',0,0);
	keyboard('y', 0, 0);
	glutTimerFunc(n, timer_func, n);
}
void init()
{
	c.G = 0x0f;
	glClearColor(0x00, 0x00, 0x00, 0x00);
	glShadeModel(GL_FLAT);
}
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0xFF, 0xFF, 0x00);
	glPushMatrix();

	glutSolidSphere(1.0, 20, 16);
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
	planet(0.2f, 2.0f, day, c);
	glPopMatrix();
	glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ('d') :
		day = (day + 10) % 360;
		glutPostRedisplay();
		break;
	case ('D') :
		day = (day - 10) % 360;
		glutPostRedisplay();
		break;
	case ('y') :
		year = (year + 5) % 360;
		glutPostRedisplay();
		break;
	case ('Y') :
		year = (year - 5) % 360;
		glutPostRedisplay();
		break;
	default: 
		break;
	}
}