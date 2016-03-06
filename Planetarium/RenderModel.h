#pragma once
#include "RenderItem.h"
#include "util.h"
class RenderModel
{
private:
	RenderItem** Items;
	int itemsCount;
	//look at settings
	GLdouble eyex = 0.0, eyey = 5.0, eyez = 5.0, centerX = 0.0, centerY = 0.0, centerZ = 0.0, upX = 0.0, upY = 1.0, upZ = 0.0;
	int rightMouseState = GLUT_UP, leftMouseState = GLUT_UP;
	int width, height;
	GLdouble currentMouseX, currentMouseY;
	GLfloat *light_position;
public:
	static RenderModel* CurrentModel;
	~RenderModel();
	void init();
	void display(void);
	void reshape(int width, int height);
	void keyboard(unsigned char key, int x, int y);
	void mouseWheel(int wheel, int direction, int x, int y);
	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void setCamera();
	void takeMousePosition(int x, int y);

	//glut callbacks
	static void displayCallBack();
	static void reshapeCallBack(int width, int height);
	static void keyboardCallBack(unsigned char key, int x, int y);
	static void timerFuncCallBack(int n);
	static void mouseWheelCallBack(int wheel, int direction, int x, int y);
	static void mouseCallBack(int button, int state, int x, int y);
	static void motionCallBack(int x, int y);
};