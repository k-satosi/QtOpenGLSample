#pragma once

#include "Object.h"

class Plane : public Object
{
public:
	Plane(QVector3D &normal);

protected:
	void draw();
};
