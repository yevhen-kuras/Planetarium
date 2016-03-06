#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\freeglut\glut.h"
#include "util.h"
#include "RenderItem.h"
#include "Planet.h"
#include "RenderModel.h"

Planet::Planet(GLdouble radius, GLdouble dist, GLdouble startOrbitRotateAngle, Color solidColor)
{
	this->dist = dist;
	this->radius = radius;
	this->orbitRotateAngle = startOrbitRotateAngle;
	this->solidColor = solidColor;
}

void Planet::SetIsOrbitRotationEnabled(bool isOrbitRotationEnabled)
{
	this->isOrbitRotationEnabled = isOrbitRotationEnabled;
	//asdasd
}

bool Planet::GetIsOrbitRotationEnabled() const
{
	return isOrbitRotationEnabled;
}

void Planet::SetOrbitRotationAngleDelta(float orbitRotationAngleDelta)
{
	this->orbitRotationAngleDelta = orbitRotationAngleDelta;
}

GLdouble Planet::GetOrbitRotationAngleDelta() const
{
	return orbitRotationAngleDelta;
}

void Planet::SetDist(GLdouble dist)
{
	this->dist = dist;
}

GLdouble Planet::GetDist() const
{
	return dist;
}

void Planet::SetRadius(GLdouble radius)
{
	this->radius = radius;
}

GLdouble Planet::GetRadius() const
{
	return radius;
}

void Planet::Draw()
{
	if (isOrbitRotationEnabled)
	{
		glPushMatrix();
		glRotatef(orbitRotateAngle, 0.0, 1.0, 0.0);
		orbitRotateAngle += orbitRotationAngleDelta;
	}
	glPushMatrix();
	glColor3ub(solidColor.R, solidColor.G, solidColor.B);
	glTranslatef(dist, 0.0, 0.0);
	glutSolidSphere(radius, 100, 50);
	glPopMatrix();
	if (isOrbitRotationEnabled)
	{
		glPopMatrix();
	}
}