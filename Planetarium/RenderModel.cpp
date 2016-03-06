#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\freeglut\glut.h"
#include "util.h"
#include "Planet.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "RenderModel.h"
#include "RenderItem.h"
#include "Planet.h"

RenderModel* RenderModel::CurrentModel = NULL;

void RenderModel::init()
{
	itemsCount = 9;
	Items = new RenderItem*[itemsCount];
	//Сонце
	//Items[0] = new Planet(0.4, 0, 0.0f, Color(0xff, 0xff, 0x00));
	Planet* sun = new Planet(696342000, 0, 0, Color(0xff, 0xff, 0x00));
	Items[0] = sun;
	//Меркурій
	//Items[1] = new Planet(0.1, 0.5, 0.0f, Color(0x0f, 0x0f, 0x00));
	Items[1] = new Planet(2439700,sun->GetRadius() + 46080000, 0.0f, Color(0x0f, 0x0f, 0x00));
	//Венера
	//Items[2] = new Planet(0.3, 1, 25.0f, Color(0xff, 0xfe, 0xfe));
	Items[2] = new Planet(6051800, sun->GetRadius() + 107476259, 50.0f, Color(0xff, 0xfe, 0xfe));
	//Земля
	//Items[3] = new Planet(0.25, 1.5, 36.0f, Color(0x00, 0x00, 0xff));
	Items[3] = new Planet(6371300, sun->GetRadius() + 147098290, 10.0f, Color(0x00, 0x00, 0xff));
	//Марс
	//Items[4] = new Planet(0.18, 1.9, 80.0f, Color(0x0f, 0x0f, 0xfe));
	Items[4] = new Planet(3396200, sun->GetRadius() + 206669000, 270.0f, Color(0x0f, 0x0f, 0xfe));
	//Юпітер
	//Items[5] = new Planet(1, 2.2, -90.0f, Color(0xff, 0x0e, 0x0d));
	Items[5] = new Planet(69911000, sun->GetRadius() + 740000000, 100.0f, Color(0xff, 0x0e, 0x0d));
	//Сатурн
	//Items[6] = new Planet(0.7, 2.6, 90.0f, Color(0xff, 0x00, 0xff));
	Items[6] = new Planet(60268000, sun->GetRadius() + 1353572956, 90.0f, Color(0xff, 0x00, 0xff));
	//Уран
	//Items[7] = new Planet(0.4, 2.9, 270.0f, Color(0xff, 0xff, 0xff));
	Items[7] = new Planet(25559000, sun->GetRadius() + 2748938461, 50.0f, Color(0xff, 0xff, 0xff));
	//Нептун
	//Items[8] = new Planet(0.5, 3.2, 180.0f, Color(0xff, 0x1f, 0x01));
	Items[8] = new Planet(24764000, sun->GetRadius() + 4452940833, 36.0f, Color(0xff, 0x1f, 0x01));
	for (int i = 1; i < itemsCount; i++)
	{
		Planet* planet = (Planet*)Items[i];
		planet->SetIsOrbitRotationEnabled(true);
		planet->SetOrbitRotationAngleDelta(((itemsCount - i)*1.5f + 1)/10);
	}
	GLdouble maxDist = ((Planet*)Items[1])->GetDist();
	for (int i = 2; i < itemsCount; i++)
	{
		Planet* planet = (Planet*)Items[i];
		GLdouble dist = planet->GetDist();
		if (dist > maxDist)
		{
			maxDist = dist;
		}
	}
	eyey = maxDist;
	setCamera();
	glClearColor(0x00, 0x00, 0x00, 0x00);
	glutDisplayFunc(RenderModel::displayCallBack);
	glutReshapeFunc(RenderModel::reshapeCallBack);
	glutKeyboardFunc(RenderModel::keyboardCallBack);
	glutMouseWheelFunc(RenderModel::mouseWheelCallBack);
	glutMotionFunc(RenderModel::motionCallBack);
	glutMouseFunc(mouseCallBack);

	GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat white_light[] = { 1.0,1.0,1.0,1.0 };
	light_position = new GLfloat[4]{ 1.0,1.0,1.0,1.0 };
	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	RenderModel::timerFuncCallBack(50);
}

void RenderModel::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glColor3f(0xFF, 0xFF, 0x00);
	//glPushMatrix();
	
	//glutSolidSphere(1.0, 100, 50);
	/*glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
	planet(0.2, 2, day, c);*/
	if (Items != NULL)
	{
		//for (RenderItem *ri = Items[0], *end = (Items[count - 1]); ri != end; ri++)
		for (int i = 0; i < itemsCount; i++)
		{
			Items[i]->Draw();
		}
	}
	//glPopMatrix();
	glutSwapBuffers();

	/*eyey += 1;
	eyex += 1;
	eyez += 1;
	setCamera();*/
}
void RenderModel::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case('1') :
		eyey += 2;
		std::cout << "up eye y: " << eyey << std::endl;
		setCamera();
		break;
	case('2') :
		eyey -= 2;
		std::cout << "down eye y: " << eyey << std::endl;
		setCamera();
		break;
	}
	//gluLookAt(0.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void RenderModel::mouseWheel(int wheel, int direction, int x, int y)
{
	light_position[0]+=1000;
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	return;
	GLdouble newEyeY = eyey - direction;
	if (signbit(newEyeY) == signbit(eyey))
	{
		eyey = newEyeY;
		setCamera();
	}
}
void RenderModel::mouse(int button, int state, int x, int y)
{
	bool up = state == GLUT_UP;
	switch (button)
	{
	case(GLUT_LEFT_BUTTON) :
		leftMouseState = state;
		if (state == GLUT_DOWN)
		{
			takeMousePosition(x, y);
		}
		//std::cout << "left " << (up ? "up" : "down") << std::endl;
		break;
	case(GLUT_RIGHT_BUTTON) :
		rightMouseState = state;
		//std::cout << "right " << (up ? "up" : "down") << std::endl;
		break;
	}
	//// Wheel reports as button 3(scroll up) and button 4(scroll down)
	//if ((button == 3) || (button == 4)) // It's a wheel event
	//{
	//	// Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
	//	if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
	//	printf("Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y);
	//}
	//else {  // normal button event
	//	printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
	//}
}
void RenderModel::motion(int x, int y)
{
	if (leftMouseState == GLUT_DOWN)
	{
		GLdouble prevX = currentMouseX;
		GLdouble prevY = currentMouseY;
		takeMousePosition(x, y);
		centerX -= (prevX - currentMouseX)*2;
		centerY -= (prevY - currentMouseY)*5;
		setCamera();
 	}
}

void RenderModel::reshape(int newWidth, int newHeight)
{
	this->width = newWidth;
	this->height = newHeight;
	setCamera();
}
void RenderModel::setCamera()
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, abs(centerX- eyex ));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, centerX, centerY, centerZ, upX, upY, upZ);
	glutPostRedisplay();
}
void RenderModel::takeMousePosition(int x, int y)
{
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16], objX, objY, objZ;
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
	gluUnProject(x, y, 0, mvmatrix, projmatrix, viewport, &objX, &objY, &objZ);
	currentMouseX = objX;
	currentMouseY = objY;
}
void RenderModel::displayCallBack()
{
	CurrentModel->display();
}
void RenderModel::reshapeCallBack(int width, int height)
{
	CurrentModel->reshape(width, height);
}
void RenderModel::keyboardCallBack(unsigned char key, int x, int y)
{
	CurrentModel->keyboard(key, x, y);
}
void RenderModel::timerFuncCallBack(int n)
{
	/*keyboard('d', 0, 0);
	keyboard('y', 0, 0);*/
	glutPostRedisplay();
	glutTimerFunc(n, RenderModel::timerFuncCallBack, n);
}
void RenderModel::mouseWheelCallBack(int wheel, int direction, int x, int y)
{

	CurrentModel->mouseWheel(wheel, direction, x, y);
}
void RenderModel::mouseCallBack(int button, int state, int x, int y)
{
	CurrentModel->mouse(button, state, x, y);
}
void RenderModel::motionCallBack(int x, int y)
{
	CurrentModel->motion(x, y);
}
RenderModel::~RenderModel()
{
	if (Items != NULL)
	{
		delete[] Items;
	}
}