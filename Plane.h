#pragma once

#include "Object.h"

class Plane : public Object
{
public:
	Plane(const QVector3D &normal);
	~Plane();

protected:
	void draw();
};
