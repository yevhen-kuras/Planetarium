#pragma once
#include"util.h"
#include"RenderItem.h"


class Planet:public RenderItem
{
protected:
	GLdouble radius;
	GLdouble dist;
	GLdouble orbitRotateAngle;
	Color solidColor;
	bool isOrbitRotationEnabled;
	GLdouble orbitRotationAngleDelta = 10;
public:
	Planet(GLdouble radius, GLdouble dist, GLdouble startOrbitRotateAngle, Color solidColor);
	virtual void Draw();
	void SetIsOrbitRotationEnabled(bool isOrbitRotationEnabled);
	bool GetIsOrbitRotationEnabled() const;
	void SetOrbitRotationAngleDelta(float orbitRotationAngleDelta);
	GLdouble GetOrbitRotationAngleDelta() const;
	void SetDist(GLdouble dist);
	GLdouble GetDist() const;
	void SetRadius(GLdouble radius);
	GLdouble GetRadius() const;
};